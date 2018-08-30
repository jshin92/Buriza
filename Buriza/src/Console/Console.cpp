#include "Console.h"

Console::Console()
    : m_row(0)
    , m_col(0)
    , m_buffer()
{
}

Console& Console::Get()
{
    static Console instance;
    return instance;
}
