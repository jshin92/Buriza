#include "Model.h"

Model::Model(const char* path)
{
    LoadModel(path);
}

void Model::Draw(const Shader& shader) const
{
    for (const auto& mesh : m_meshes)
    {
        mesh.Draw(shader);
    }
}

void Model::LoadModel(const char* path)
{
}
