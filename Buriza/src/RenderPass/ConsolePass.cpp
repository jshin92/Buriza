#include "ConsolePass.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>

ConsolePass::ConsolePass(Shader& shader, GLint width, GLint height)
    : IRenderPass(shader, width, height)
{
    GLfloat vertices[]
    {
        -0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    m_ortho = glm::ortho(0.0f, m_width * 1.0f, 0.0f, m_height * 1.0f);
    m_model = glm::mat4{};
}

IRenderPassOutput ConsolePass::Run(std::optional<IRenderPassOutput> consoleInput)
{
    auto input = std::get<ConsolePassInput>(*consoleInput);
    m_shader.Use();
    //m_shader.SetMat4("projection", m_ortho);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    return {};
}
