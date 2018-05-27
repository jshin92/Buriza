#include "DefaultPass.h"
#include <GLM/gtc/matrix_transform.hpp>

DefaultPass::DefaultPass(Shader& shader, Camera& camera)
    : IRenderPass(shader)
    , m_camera(camera)
{
}

RenderPassOutput DefaultPass::Run(std::optional<RenderPassOutput> previousPassOutput)
{
    auto shadowOutput = *previousPassOutput;
    /* then render the scene normally, using the depthMap, which contains shadow information */
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // TODO: parameterize SCREEN_WIDTH and SCREEN_HEIGHT
    GLuint width = 800;
    GLuint height = 600;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // configure shaders and matrices
    glBindTexture(GL_TEXTURE_2D, shadowOutput.depthMapTexture);
    // render the scene
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.GetFOV()), (float)width / height, 0.1f, 100.0f);

    m_shader.Use();
    m_shader.SetMat4("view", view);
    m_shader.SetMat4("projection", projection);
    m_shader.SetMat4("lightSpaceMatrix", shadowOutput.lightSpaceMatrix);
    m_shader.SetVec3("viewPos", m_camera.GetPosition());
    m_shader.SetVec3("lightPos", glm::vec3(-2.0f, 4.0f, -1.0f));
    m_shader.SetInt("diffuseTexture", 0);
    m_shader.SetInt("shadowMap", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowOutput.depthMapTexture);
    return {};
}
