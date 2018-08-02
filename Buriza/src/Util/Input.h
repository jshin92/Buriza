#pragma once

constexpr int MAX_INPUT_SIZE = 512;

struct GLFWwindow;

class Input
{
public:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static auto GetKeyState() -> const bool (&)[MAX_INPUT_SIZE];
    static auto GetDiscreteKeyPressState() -> const bool(&)[MAX_INPUT_SIZE];
    static void ResetDiscreteKeyPresses();

private:
    static bool m_keys[MAX_INPUT_SIZE];
    static bool m_discreetlyPressedKeys[MAX_INPUT_SIZE];
};
