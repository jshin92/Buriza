#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

#include "../Util/Input.h"

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
    const std::string& GetCurrentExpression() const;
    const GLuint& GetRow() const;
    Console& PushMessage(const std::string& msg, Severity sev=Severity::Info);
    void ProcessChar(GLuint codepoint);
    void ProcessKey(const bool(&discreteKeys)[MAX_INPUT_SIZE]);

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

