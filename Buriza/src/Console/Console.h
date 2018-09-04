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
    static Console& Instance();

    const std::vector<std::string>& GetBuffer() const;
    Console& PushMessage(const std::string& msg, Severity sev=Severity::Info);
    void ProcessChar(GLuint codepoint);
    void ProcessKey();

    Console(const Console&) = delete;
    Console(const Console&&) = delete;
    Console& operator=(const Console&) = delete;
    Console& operator=(const Console&&) = delete;

private:
    static Console instance;

    Console();
    virtual ~Console() = default;

    std::string m_currentExpression;
    std::vector<std::string> m_buffer;
    GLuint m_row;
    GLuint m_col;
};

