#include "Entity.h"

Entity::Entity(const std::string& modelPath, const glm::vec3& position, GLfloat scale)
    : m_modelData(modelPath.c_str())
{
    m_model = glm::mat4{};
    m_model = glm::translate(m_model, position);
    m_model = glm::scale(m_model, glm::vec3(scale));
}

void Entity::Tick()
{
    m_model = glm::rotate(m_model, 0.003f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Entity::Draw(const Shader& shader)
{
    shader.SetMat4("model", m_model);
    m_modelData.Draw(shader);
}
