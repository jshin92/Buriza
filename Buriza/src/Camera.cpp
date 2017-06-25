#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp, float speed)
    : m_cameraPos(cameraPos)
    , m_cameraFront(cameraFront)
    , m_cameraUp(cameraUp)
    , m_speed(speed)
{}

const glm::vec3& Camera::GetCameraPos() const
{
    return m_cameraPos;
}

const glm::vec3& Camera::GetCameraFront() const
{
    return m_cameraFront;
}

const glm::vec3& Camera::GetCameraUp() const
{
    return m_cameraUp;
}

void Camera::SetCameraPos(const glm::vec3& cameraPos)
{
    m_cameraPos = cameraPos;
}

void Camera::SetCameraFront(const glm::vec3& cameraFront)
{
    m_cameraFront = cameraFront;
}

void Camera::SetCameraUp(const glm::vec3& cameraUp)
{
    m_cameraUp = cameraUp;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void Camera::ProcessKeyboard(CameraMovement direction, double deltaTime)
{
    float velocity = m_speed * (float) deltaTime;
    if (direction == CameraMovement::FORWARD)
        m_cameraPos += m_cameraFront * velocity;
    if (direction == CameraMovement::BACKWARD)
        m_cameraPos -= m_cameraFront * velocity;
    if (direction == CameraMovement::LEFT)
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * velocity;
    if (direction == CameraMovement::RIGHT)
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * velocity;
}



