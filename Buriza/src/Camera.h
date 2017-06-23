#pragma once

#include <GLM/glm.hpp>

class Camera
{
public:
    Camera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp);
    glm::vec3& GetCameraPos();
    glm::vec3& GetCameraFront();
    glm::vec3& GetCameraUp();
    void SetCameraPos(const glm::vec3& cameraPos);
    void SetCameraFront(const glm::vec3& cameraFront);
    void SetCameraUp(const glm::vec3& cameraUp);
    glm::mat4 GetViewMatrix();

    virtual ~Camera() = default;

private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;
};

