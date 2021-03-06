#pragma once

#include "IRenderPass.h"

class CursorPass : public IRenderPass
{
public:
    CursorPass(Shader& shader, GLint width, GLint height, GLfloat scale);
    IRenderPassOutput Run(std::optional<IRenderPassOutput>);
    ~CursorPass() = default;

private:
    GLuint m_texture;
    GLuint m_vao;
    GLuint m_vbo;
    glm::mat4 m_ortho;
};

