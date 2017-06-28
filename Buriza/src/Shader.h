#pragma once

#include <GL/glew.h>
#include <GLM/gtc/type_ptr.hpp>


class Shader
{
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader() = default;
    void Use() const;
    GLuint getProgram() const;
    void SetVec3(const char* target, GLfloat x, GLfloat y, GLfloat z);
    void SetMat4(const char* target, glm::mat4& matrix);

private:
    GLuint m_program;
};

