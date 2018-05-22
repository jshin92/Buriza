#pragma once

#include <GLM/gtc/matrix_transform.hpp>
#include "Model.h"

class Entity
{
public:
    Entity(const std::string& modelPath, const glm::vec3& position, GLfloat scale=1.0f);
    virtual ~Entity() = default;

    void Draw(const Shader& shader);
private:
    Model m_modelData;
    glm::mat4 m_model;
};

