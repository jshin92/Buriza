#pragma once

#include <GL/glew.h>
#include <functional>
#include <optional>
#include <string>

struct TextureUtil
{
    static GLuint TextureFromFile(const char* path, const std::string& directory);
    static GLuint TextureFromFile(const char* fullPath, std::optional<std::function<void()>> filterFunc);
    TextureUtil() = delete;
    ~TextureUtil() = delete;
};

