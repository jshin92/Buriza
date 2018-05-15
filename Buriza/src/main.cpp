#define GLEW_STATIC

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Input.h"
#include "Model.h"
#include "Shader.h"
#include "TextRenderer.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
double lastX = SCREEN_WIDTH / 2;
double lastY = SCREEN_HEIGHT / 2;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double deltaTime = 0.0; // Time between current frame and last frame
double lastFrame = 0.0; // Time of the last frame
bool firstMouse = true;

int main()
{
    std::cout << "Initializing Buriza..." << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Buriza", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, Input::KeyCallback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Shader modelShader("shaders/model_loading.vs", "shaders/model_loading.fs");
    Model cube("assets/cube_textured/cube_textured.obj");
    Model cube2("assets/cube_textured/cube_textured.obj");
    Model plane("assets/plane.obj");

    TextRenderer textRenderer{SCREEN_WIDTH, SCREEN_HEIGHT, "fonts/arial.ttf", "shaders/text.vs", "shaders/text.fs"};

    while (!glfwWindowShouldClose(window))
    {
        // Calculate deltatime of current frame
        GLfloat currentFrame = (GLfloat)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        GLfloat fps = 1.0f / (GLfloat) deltaTime;

        glfwPollEvents();
        ProcessInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model{};
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetFOV()), (float)width / height, 0.1f, 100.0f);

        modelShader.Use();
        modelShader.SetMat4("view", view);
        modelShader.SetMat4("projection", projection);

        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        modelShader.SetMat4("model", model);
        plane.Draw(modelShader);

        model = glm::mat4{};
        model = glm::scale(model, glm::vec3(0.5f));
        modelShader.SetMat4("model", model);
        cube.Draw(modelShader);

        model = glm::mat4{};
        model = glm::translate(model, glm::vec3(0.5f, 0.0f, -2.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        modelShader.SetMat4("model", model);
        cube2.Draw(modelShader);

        glBindVertexArray(0);

        textRenderer.Draw(std::to_string(fps), glm::vec2(25.0f, 565.0f), glm::vec3(0.5f, 0.8f, 0.2f));
        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // reversed since ycoords range from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
