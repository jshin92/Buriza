#define GLEW_STATIC

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Entity/Entity.h"
#include "Entity/Model.h"
#include "Util/Input.h"
#include "Util/Shader.h"
#include "Util/TextRenderer.h"
#include "Render/ShadowPass.h"
#include "Render/DefaultPass.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
double lastX = SCREEN_WIDTH / 2;
double lastY = SCREEN_HEIGHT / 2;

Camera camera(glm::vec3(0.5f, 0.7f, 3.8f));
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

    glEnable(GL_CULL_FACE);
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

    Shader simpleDepthShader("shaders/simpleDepthShader");
    Shader modelShader("shaders/model_loading");
    Shader shadowShader("shaders/shadow");

    Entity cube("assets/cube_textured/cube_textured.obj", glm::vec3(0.0f, 1.0f, 0.0f));
    Entity plane("assets/plane.obj", glm::vec3(0.0f, 0.0f, 0.0f), 4.0f);
    Entity hero("assets/hero/hero.obj", glm::vec3(0.5f, 0.6f, 2.0f), 0.25f);

    TextRenderer textRenderer{SCREEN_WIDTH, SCREEN_HEIGHT, "fonts/arial.ttf", "shaders/text.vs", "shaders/text.fs"};

    ShadowPass shadowPass{simpleDepthShader};
    DefaultPass defaultPass{shadowShader, camera};

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

        RenderPassOutput shadowOutput = shadowPass.Run({});
        plane.Draw(simpleDepthShader);
        cube.Draw(simpleDepthShader);
        hero.Draw(simpleDepthShader);

        defaultPass.Run(shadowOutput);
        plane.Draw(shadowShader);
        cube.Draw(shadowShader);
        hero.Draw(shadowShader);

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

    const auto& keyState = Input::GetKeyState();

    camera.ProcessDirection(keyState, deltaTime);
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
