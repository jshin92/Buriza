#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

enum class Severity
{
    Info,
    Warn,
    Error
};

class Console
{
public:
    static Console& Get();
    static const std::vector<std::string>& GetBuffer();
    static void PushMessage(const std::string& msg, Severity sev=Severity::Info);

    Console(const Console&) = delete;
    Console(const Console&&) = delete;
    Console& operator=(const Console&) = delete;
    Console& operator=(const Console&&) = delete;

private:
    static Console instance;

    Console();
    virtual ~Console() = default;

    static std::vector<std::string> buffer;
    GLuint m_row;
    GLuint m_col;
};

