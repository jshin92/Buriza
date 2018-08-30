#pragma once
#include "IRenderPass.h"

class ConsolePass : public IRenderPass
{
public:
    ConsolePass(Shader& shader, GLint width, GLint height);
    IRenderPassOutput Run(std::optional<IRenderPassOutput>);
    ~ConsolePass() = default;

private:
    GLuint m_vao;
    GLuint m_vbo;
    glm::mat4 m_ortho;
    glm::mat4 m_model;
};

