#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>

#include "ConsolePass.h"
#include "../Console/Console.h"
#include "../Util/TextRenderer.h"

ConsolePass::ConsolePass(Shader& shader, GLint screenWidth, GLint screenHeight, GLint consoleWidth, GLint consoleHeight)
    : IRenderPass(shader, screenWidth, screenHeight)
{
    GLfloat vertices[]
    {
        0.0f               , 0.f,
        consoleWidth * 1.0f, consoleHeight * 1.0f,
        0.0f               , consoleHeight * 1.0f,
        0.0f               , 0.0f,
        consoleWidth * 1.0f, 0.0f,
        consoleWidth * 1.0f, consoleHeight * 1.0f
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    m_ortho = glm::ortho(0.0f, m_width * 1.0f, 0.0f, m_height * 1.0f);
    m_model = glm::translate(m_model, glm::vec3(0, m_height - consoleHeight, 0));
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
}

IRenderPassOutput ConsolePass::Run(std::optional<IRenderPassOutput> consoleInput)
{
    const auto& consoleInstance = Console::Instance();
    const auto& buffer = consoleInstance.GetBuffer();
    const auto& currentExpression = consoleInstance.GetCurrentExpression();
    const auto& currentRow = consoleInstance.GetRow();

    auto input = std::get<ConsolePassInput>(*consoleInput);
    m_shader.Use();
    m_shader.SetMat4("projection", m_ortho);
    m_shader.SetMat4("model", m_model);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    input.textRenderer.Draw(currentExpression, glm::vec2(LEFT_PAD, m_screenHeight - TOP_PAD - BLOCKSIZE * currentRow), glm::vec3(1.0, 0.2, 0.2));

    return {};
}
