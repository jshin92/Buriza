#pragma once
#include "IRenderPass.h"

class ConsolePass : public IRenderPass
{
public:
    ConsolePass(Shader& shader, GLint windowWidth, GLint windowHeight, GLint consoleWidth, GLint consoleHeight);
    IRenderPassOutput Run(std::optional<IRenderPassOutput>);
    ~ConsolePass() = default;

private:
    GLuint m_vao;
    GLuint m_vbo;
    glm::mat4 m_ortho;
    glm::mat4 m_model;
};

