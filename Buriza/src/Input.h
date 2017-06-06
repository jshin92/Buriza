#pragma once

constexpr int MAX_INPUT_SIZE = 1024;

struct GLFWwindow;

class Input
{
public:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static auto GetKeyState() -> const bool (&)[MAX_INPUT_SIZE];

private:
    static bool m_keys[MAX_INPUT_SIZE];
};