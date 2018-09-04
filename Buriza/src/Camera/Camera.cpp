#include <GLM/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Camera.h"

constexpr GLfloat DEFAULT_SPEED = 10.5f;
constexpr GLfloat DEFAULT_FOV = 45.0f;
constexpr GLfloat DEFAULT_SENSITIVITY = 0.05f;

Camera::Camera(const glm::vec3& position, const glm::vec3& up, const glm::vec3& front, GLfloat yaw, GLfloat pitch)
    : m_position(position)
    , m_front(front)
    , m_up(up)
    , m_yaw(yaw)
    , m_pitch(pitch)
    , m_speed(DEFAULT_SPEED)
    , m_fov(DEFAULT_FOV)
    , m_sensitivity(DEFAULT_SENSITIVITY)
{}

const glm::vec3& Camera::GetPosition() const
{
    return m_position;
}

const glm::vec3& Camera::GetFront() const
{
    return m_front;
}

const glm::vec3& Camera::GetUp() const
{
    return m_up;
}

float Camera::GetFOV() const
{
    return m_fov;
}

void Camera::SetPosition(const glm::vec3& cameraPos)
{
    m_position = cameraPos;
}

void Camera::SetFront(const glm::vec3& cameraFront)
{
    m_front = cameraFront;
}

void Camera::SetUp(const glm::vec3& cameraUp)
{
    m_up = cameraUp;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::ProcessDirection(const bool(&keys)[MAX_INPUT_SIZE], double deltaTime)
{
    if (keys[GLFW_KEY_W])
        ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
}

void Camera::ProcessKeyboard(CameraMovement direction, double deltaTime)
{
    float velocity = m_speed * (float) deltaTime;
    if (direction == CameraMovement::FORWARD)
        m_position += m_front * velocity;
    if (direction == CameraMovement::BACKWARD)
        m_position -= m_front * velocity;
    if (direction == CameraMovement::LEFT)
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * velocity;
    if (direction == CameraMovement::RIGHT)
        m_position += glm::normalize(glm::cross(m_front, m_up)) * velocity;
}

void Camera::ProcessMouseScroll(double yoffset)
{
    if (m_fov >= 1.0f && m_fov <= 45.0f)
        m_fov -= (GLfloat)yoffset;
    if (m_fov <= 1.0f)
        m_fov = 1.0f;
    if (m_fov >= 45.0f)
        m_fov = 45.0f;
}

void Camera::ProcessMouseMovement(double xoffset, double yoffset)
{
    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw += (GLfloat)xoffset;
    m_pitch += (GLfloat)yoffset;

    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0) m_pitch = -89.0f;

    glm::vec3 front{};
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
}
