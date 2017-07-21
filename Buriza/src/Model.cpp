#include <iostream>
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/postprocess.h>
#include "Model.h"

Model::Model(const char* path)
{
    LoadModel(std::string(path));
}

void Model::Draw(const Shader& shader) const
{
    for (const auto& mesh : m_meshes)
    {
        mesh.Draw(shader);
    }
}

// todo: change this back to all take in conist char * and convert inside
void Model::LoadModel(const std::string& path)
{
    Assimp::Importer importer{};
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP" << importer.GetErrorString() << std::endl;
        return;
    }
    m_directory = path.substr(0, path.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
}
