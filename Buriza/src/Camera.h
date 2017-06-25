#pragma once

#include <GLM/glm.hpp>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

constexpr float DEFAULT_SPEED = 2.5f;

class Camera
{
public:
    Camera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp, float speed=DEFAULT_SPEED);
    const glm::vec3& GetCameraPos() const;
    const glm::vec3& GetCameraFront() const;
    const glm::vec3& GetCameraUp() const;
    void SetCameraPos(const glm::vec3& cameraPos);
    void SetCameraFront(const glm::vec3& cameraFront);
    void SetCameraUp(const glm::vec3& cameraUp);
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(CameraMovement direction, double deltaTime);

    virtual ~Camera() = default;

private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;

    float m_speed;
};

