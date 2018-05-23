#pragma once

#include <GL/glew.h>
#include <GLM/fwd.hpp>


class Shader
{
public:
    Shader(const GLchar* path);
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader() = default;
    void Use() const;
    GLuint getProgram() const;
    void SetVec3(const char* target, GLfloat x, GLfloat y, GLfloat z) const;
    void SetVec3(const char* target, const glm::vec3& v) const;
    void SetMat4(const char* target, const glm::mat4& matrix) const;
    void SetFloat(const char* target, GLfloat val) const;
    void SetInt(const char* target, GLint val) const;

private:
    GLuint m_program;
};

