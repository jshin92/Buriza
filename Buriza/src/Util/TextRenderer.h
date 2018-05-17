#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "Shader.h"

struct Character
{
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint Advance;
};

class TextRenderer
{
public:
    TextRenderer(int width, int height, const char* fontname, const char* vertexShaderCode, const char* fragmentShaderCode);
    virtual ~TextRenderer() = default;
    void Draw(std::string text, glm::vec2 coord, glm::vec3 color, GLfloat scale=1.0f);

private:
    GLuint m_vao;
    GLuint m_vbo;
    Shader m_shader;
    std::vector<Character> m_characters;
    glm::mat4 m_ortho;
};

