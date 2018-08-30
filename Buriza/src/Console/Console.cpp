#include "Console.h"

std::vector<std::string> Console::buffer{};

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
