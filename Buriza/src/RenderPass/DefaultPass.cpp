#include "DefaultPass.h"
#include "ShadowPass.h"
#include <GLM/gtc/matrix_transform.hpp>

DefaultPass::DefaultPass(Shader& shader, int width, int height, Camera& camera)
    : IRenderPass(shader, width, height)
    , m_camera(camera)
{
}

IRenderPassOutput DefaultPass::Run(std::optional<IRenderPassOutput> previousPassOutput)
{
    auto shadowOutput = std::get<ShadowPassOutput>(*previousPassOutput);
    /* then render the scene normally, using the depthMap, which contains shadow information */
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // configure shaders and matrices
    glBindTexture(GL_TEXTURE_2D, shadowOutput.depthMapTexture);
    // render the scene
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.GetFOV()), (float)m_width / m_height, 0.1f, 100.0f);

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
