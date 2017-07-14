#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "shader.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

enum class TextureType
{
    DIFFUSE,
    SPECULAR
};

struct Texture
{
    GLuint id;
    TextureType type;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
    virtual ~Mesh() = default;
    void Draw(const Shader& shader);

private:
    /* Render data */
    GLuint m_VAO, m_VBO, m_EBO;
    /* Mesh data */
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    std::vector<Texture> m_textures;
    void SetupMesh();
};

