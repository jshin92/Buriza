#pragma once

#include <GL/glew.h>

class Shader
{
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader() = default;
    void Use() const;
    GLuint getProgram() const;

private:
    GLuint m_program;
};

