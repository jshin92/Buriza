#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

constexpr GLfloat DEFAULT_SPEED = 2.5f;
constexpr GLfloat DEFAULT_FOV = 45.0f;

class Camera
{
public:
    Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up,
           GLfloat speed=DEFAULT_SPEED, GLfloat fov=DEFAULT_FOV);
    const glm::vec3& GetCameraPosition() const;
    const glm::vec3& GetCameraFront() const;
    const glm::vec3& GetCameraUp() const;
    float GetFOV() const;
    void SetCameraPos(const glm::vec3& cameraPos);
    void SetCameraFront(const glm::vec3& cameraFront);
    void SetCameraUp(const glm::vec3& cameraUp);
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(CameraMovement direction, double deltaTime);
    void ProcessMouseScroll(double yoffset);

    virtual ~Camera() = default;

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;

    GLfloat m_speed;
    GLfloat m_fov;
};

