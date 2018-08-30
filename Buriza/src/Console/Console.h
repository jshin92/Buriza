#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

class Console
{
public:
    static Console& Get();

    Console(const Console&) = delete;
    Console(const Console&&) = delete;
    Console& operator=(const Console&) = delete;
    Console& operator=(const Console&&) = delete;

private:
    static Console instance;

    Console();
    virtual ~Console() = default;

    std::vector<std::string> m_buffer;
    GLuint m_row;
    GLuint m_col;
};

