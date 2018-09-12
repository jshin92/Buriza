#include "Console.h"
#include <iostream>
#include <GLFW/glfw3.h>

namespace
{
    std::string SeverityToString(Severity sev)
    {
        if (sev == Severity::Info) return "[INFO]: ";
        else if (sev == Severity::Warn) return "[WARN]: ";
        else if (sev == Severity::Error) return "[ERR]:  ";
        else return "[UNRECOGNIZED]: ";
    }
}


Console::Console()
    : m_row(0)
    , m_col(0)
    , m_buffer()
    , m_currentExpression()
{
}

Console& Console::Instance()
{
    static Console instance;
    return instance;
}

const std::vector<std::string>& Console::GetBuffer() const
{
    return m_buffer;
}

const std::string& Console::GetCurrentExpression() const
{
    return m_currentExpression;
}

const GLuint& Console::GetRow() const
{
    return m_row;
}

Console& Console::PushMessage(const std::string& msg, Severity sev)
{
    m_buffer.emplace_back(SeverityToString(sev) + msg);
    return *this;
}

void Console::ProcessChar(GLuint codepoint)
{
    // ignore backticks, as that's how you open the console
    if (codepoint == GLFW_KEY_GRAVE_ACCENT) return;

    m_currentExpression += (char)codepoint;
}

void Console::ProcessKey(const bool(&discreteKeys)[MAX_INPUT_SIZE])
{
    if (discreteKeys[GLFW_KEY_ENTER])
    {
        m_buffer.push_back(m_currentExpression);
        m_currentExpression = "";
    }
    else if (discreteKeys[GLFW_KEY_BACKSPACE])
    {
        m_currentExpression.pop_back();
    }
}
