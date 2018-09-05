#include "TextureUtil.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

GLuint TextureUtil::TextureFromFile(const char* path, const std::string& directory)
{
    return TextureUtil::TextureFromFile((directory + "/" + path).c_str(), std::nullopt);
}

GLuint TextureUtil::TextureFromFile(const char* fullPath, std::optional<std::function<void()>> filterFunc)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    GLint width, height, numComponents;
    stbi_set_flip_vertically_on_load(false);
    GLubyte* data = stbi_load(fullPath, &width, &height, &numComponents, 0);
    if (data)
    {
        GLenum format;
        if (numComponents == 1) format = GL_RED;
        else if (numComponents == 3) format = GL_RGB;
        else if (numComponents == 4) format = GL_RGBA;
        else std::cerr << "Unmatched numComponents: " << numComponents << std::endl;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        if (filterFunc) (*filterFunc)();
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

    }
    else
    {
        std::cerr << "Texture failed to load at path: " << fullPath << std::endl;
    }
    stbi_image_free(data);
    return textureID;
}
