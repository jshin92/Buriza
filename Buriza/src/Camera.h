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

constexpr GLfloat DEFAULT_PITCH = 0.0f;
constexpr GLfloat DEFAULT_YAW = -90.0f;
const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 DEFAULT_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 DEFAULT_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);

class Camera
{
public:
    Camera(const glm::vec3& position=DEFAULT_POSITION, const glm::vec3& up=DEFAULT_UP, const glm::vec3& front=DEFAULT_FRONT,
           GLfloat yaw=DEFAULT_YAW, GLfloat pitch=DEFAULT_PITCH);
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
    void ProcessMouseMovement(double xoffset, double yoffset);

    virtual ~Camera() = default;

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;

    GLfloat m_yaw;
    GLfloat m_pitch;
    GLfloat m_speed;
    GLfloat m_fov;
    GLfloat m_sensitivity;
};

