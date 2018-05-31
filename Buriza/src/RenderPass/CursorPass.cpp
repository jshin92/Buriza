#include "CursorPass.h"

#include <iostream>
#include <STB/stb_image.h>
#include <GLM/gtc/matrix_transform.hpp>

CursorPass::CursorPass(Shader& shader, GLfloat scale)
    : IRenderPass(shader)
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("assets/cursor/cursor.png", &textureWidth, &textureHeight, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "error loading texture";
    }
    stbi_image_free(data);

    GLfloat vertices[]{
         scale,  scale, 0.0f, 1.0f, 1.0f, // top right
        -scale,  scale, 0.0f, 0.0f, 1.0f, // top left
         scale, -scale, 0.0f, 1.0f, 0.0f, // bottom right
        -scale,  scale, 0.0f, 0.0f, 1.0f, // top left
        -scale, -scale, 0.0f, 0.0f, 0.0f, // bottom left
         scale, -scale, 0.0f, 1.0f, 0.0f, // bottom right
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // todo: parameterize
    int width = 800;
    int height = 600;
    m_ortho = glm::ortho(0.0f, width * 1.0f, 0.0f, height * 1.0f);
}

IRenderPassOutput CursorPass::Run(std::optional<IRenderPassOutput> cursorInput)
{
    auto coords = std::get<CursorPassInput>(*cursorInput);
    m_shader.Use();
    m_shader.SetMat4("projection", m_ortho);
    auto model = glm::mat4{};
    model = glm::translate(model, glm::vec3(coords.x, coords.y, 0.0f));
    m_shader.SetMat4("model", model);

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    return {};
}

