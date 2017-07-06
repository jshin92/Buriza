#define GLEW_STATIC

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>

#include "Camera.h"
#include "Input.h"
#include "Shader.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);
GLuint LoadTexture(const char* imageLocation);

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

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, Input::KeyCallback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    GLfloat vertices[]
    {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    GLushort indices[]
    {
        0, 1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18,
        19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 
        31, 32, 33, 34, 35, 36
    };

    glm::vec3 boxPositions[]
    {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[]
    {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    GLuint cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    GLuint diffuseMap = LoadTexture("assets/container2.png");
    GLuint specularMap = LoadTexture("assets/container2_specular.png");

    Shader lampShader("src/shaders/basic_lighting.vs", "src/shaders/lamp.fs");
    Shader lightingShader("src/shaders/basic_lighting.vs", "src/shaders/basic_lighting.fs");

    glm::vec3 boxPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Calculate deltatime of current frame
        GLfloat currentFrame = (GLfloat)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        ProcessInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render cube
        lightingShader.Use();
        lightingShader.SetVec3("viewPos", camera.GetPosition());

        // directional light
        lightingShader.SetVec3("directionalLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.SetVec3("directionalLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.SetVec3("directionalLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader.SetVec3("directionalLight.specular", 0.5f, 0.5f, 0.5f);

        // point light 1
        lightingShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
        lightingShader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.SetFloat("pointLights[0].constant", 1.0f);
        lightingShader.SetFloat("pointLights[0].linear", 0.09f);
        lightingShader.SetFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        lightingShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
        lightingShader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.SetFloat("pointLights[1].constant", 1.0f);
        lightingShader.SetFloat("pointLights[1].linear", 0.09f);
        lightingShader.SetFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        lightingShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
        lightingShader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.SetFloat("pointLights[2].constant", 1.0f);
        lightingShader.SetFloat("pointLights[2].linear", 0.09f);
        lightingShader.SetFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        lightingShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
        lightingShader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.SetFloat("pointLights[3].constant", 1.0f);
        lightingShader.SetFloat("pointLights[3].linear", 0.09f);
        lightingShader.SetFloat("pointLights[3].quadratic", 0.032f);

        lightingShader.SetVec3("spotLight.ambient", 0.15f, 0.15f, 0.15f);
        lightingShader.SetVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.SetFloat("spotLight.constant", 1.0f);
        lightingShader.SetFloat("spotLight.linear", 0.09f);
        lightingShader.SetFloat("spotLight.quadratic", 0.032f);
        lightingShader.SetVec3("spotLight.position", camera.GetPosition());
        lightingShader.SetVec3("spotLight.direction", camera.GetFront());
        lightingShader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

        lightingShader.SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lightingShader.SetFloat("material.shininess", 32.0f);
        lightingShader.SetInt("material.diffuse", 0);
        lightingShader.SetInt("material.specular", 1);

        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.SetMat4("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(camera.GetFOV()), (float)width / height, 0.1f, 100.0f);
        lightingShader.SetMat4("projection", projection);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        glBindVertexArray(cubeVAO);

        glm::mat4 model{};
        for (int i = 0; i < 10; ++i)
        {
            model = glm::mat4();
            model = glm::translate(model, boxPositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.SetMat4("model", model);
            glm::mat4 normal = glm::transpose(glm::inverse(model));
            lightingShader.SetMat4("normal", normal);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
        }


        // render lamps
        lampShader.Use();
        for (int i = 0; i < 4; ++i)
        {
            model = glm::mat4();
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lampShader.SetMat4("model", model);
            lampShader.SetMat4("view", view);
            lampShader.SetMat4("projection", projection);

            glBindVertexArray(lightVAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
        }

        glBindVertexArray(0);

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

GLuint LoadTexture(const char* imageLocation)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int textureWidth, textureHeight;
    unsigned char* image = SOIL_load_image(imageLocation, &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "could not load texture!" << std::endl;
    }
    SOIL_free_image_data(image);
    return textureID;
}
