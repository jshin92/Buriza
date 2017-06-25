#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up,
               GLfloat speed, GLfloat fov)
    : m_position(position)
    , m_front(front)
    , m_up(up)
    , m_speed(speed)
    , m_fov(fov)
{}

const glm::vec3& Camera::GetCameraPosition() const
{
    return m_position;
}

const glm::vec3& Camera::GetCameraFront() const
{
    return m_front;
}

const glm::vec3& Camera::GetCameraUp() const
{
    return m_up;
}

float Camera::GetFOV() const
{
    return m_fov;
}

void Camera::SetCameraPos(const glm::vec3& cameraPos)
{
    m_position = cameraPos;
}

void Camera::SetCameraFront(const glm::vec3& cameraFront)
{
    m_front = cameraFront;
}

void Camera::SetCameraUp(const glm::vec3& cameraUp)
{
    m_up = cameraUp;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
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



