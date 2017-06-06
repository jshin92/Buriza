#include <GLFW/glfw3.h>

#include "Input.h"

bool Input::m_keys[MAX_INPUT_SIZE]{};

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (action == GLFW_PRESS)
        m_keys[key] = true;
    else if (action == GLFW_RELEASE)
        m_keys[key] = false;
}

auto Input::GetKeyState() -> const bool (&)[MAX_INPUT_SIZE]
{
    return m_keys;
}

