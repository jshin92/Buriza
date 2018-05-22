#include "Entity.h"

Entity::Entity(const std::string& modelPath, const glm::vec3& position, GLfloat scale)
    : m_modelData(modelPath.c_str())
{
    m_model = glm::mat4{};
    m_model = glm::translate(m_model, position);
    m_model = glm::scale(m_model, glm::vec3(scale));
}

void Entity::Draw(const Shader& shader)
{
    shader.SetMat4("model", m_model);
    m_modelData.Draw(shader);
}
