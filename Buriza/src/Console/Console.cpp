#include "Console.h"
#include "../Util/Input.h"
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

Console& Console::PushMessage(const std::string& msg, Severity sev)
{
    m_buffer.emplace_back(SeverityToString(sev) + msg);
    return *this;
}

void Console::ProcessChar(GLuint codepoint)
{
    std::cout << codepoint << std::endl;
}

void Console::ProcessKey()
{
    const auto& toggedKeys = Input::GetDiscreteKeyPressState();
    // Char | Number | Enter | Space
}
