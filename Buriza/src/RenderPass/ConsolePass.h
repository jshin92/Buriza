#pragma once
#include "IRenderPass.h"

constexpr GLint BLOCKSIZE = 32;
constexpr GLint LEFT_PAD = 32;
constexpr GLint TOP_PAD = 32;

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
    GLint m_screenWidth;
    GLint m_screenHeight;
};

