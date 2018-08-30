#include "Console.h"
#include "../Util/Input.h"
#include <iostream>
#include <GLFW/glfw3.h>

std::vector<std::string> Console::buffer{};
std::string Console::currentExpression{};

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
{
}

Console& Console::Get()
{
    static Console instance;
    return instance;
}

const std::vector<std::string>& Console::GetBuffer()
{
    return buffer;
}

void Console::PushMessage(const std::string& msg, Severity sev)
{
    buffer.emplace_back(SeverityToString(sev) + msg);
}

void Console::ProcessChar(GLuint codepoint)
{
    std::cout << codepoint << std::endl;
}

void Console::ProcessKey()
{
}

void Console::ListenForKeyPresses(bool isRenderingConsole)
{
    if (!isRenderingConsole) return;

    const auto& toggedKeys = Input::GetDiscreteKeyPressState();

    // is pressed key char or number or enter?
    // Char | Number | Enter | Space
}
