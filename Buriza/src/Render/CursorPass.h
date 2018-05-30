#pragma once

#include "IRenderPass.h"

class CursorPass : public IRenderPass
{
public:
    CursorPass(Shader& shader);
    RenderPassOutput Run(std::optional<RenderPassOutput>);
    ~CursorPass() = default;

private:
    GLuint m_texture;
    GLuint m_vao;
    GLuint m_vbo;
};

