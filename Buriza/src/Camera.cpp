#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp)
    : m_cameraPos(cameraPos)
    , m_cameraFront(cameraFront)
    , m_cameraUp(cameraUp)
{}

glm::vec3& Camera::GetCameraPos()
{
    return m_cameraPos;
}

glm::vec3& Camera::GetCameraFront()
{
    return m_cameraFront;
}

glm::vec3& Camera::GetCameraUp()
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



