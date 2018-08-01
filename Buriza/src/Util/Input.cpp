#include <algorithm>

#include <GLFW/glfw3.h>
#include "Input.h"

bool Input::m_keys[MAX_INPUT_SIZE]{};
bool Input::m_DiscreetlyPressedKeys[MAX_INPUT_SIZE]{};

void Input::ResetDiscreteKeyPresses()
{
    std::fill(m_DiscreetlyPressedKeys, m_DiscreetlyPressedKeys + MAX_INPUT_SIZE, false);
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (action == GLFW_PRESS) m_keys[key] = true;
    else if (action == GLFW_RELEASE)
    {
        if (m_keys[key]) m_DiscreetlyPressedKeys[key] = true;
        m_keys[key] = false;
    }
}

auto Input::GetKeyState() -> const bool (&)[MAX_INPUT_SIZE]
{
    return m_keys;
}

auto Input::GetDiscreteKeyPressState() -> const bool (&)[MAX_INPUT_SIZE]
{
    return m_DiscreetlyPressedKeys;
}

