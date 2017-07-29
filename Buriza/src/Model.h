#pragma once

#include <vector>
#include <ASSIMP/material.h>
#include "Mesh.h"
#include "Shader.h"

struct aiMesh;
struct aiNode;
struct aiScene;

class Model
{
public:
    Model(const char* path);
    void Draw(const Shader& shader) const;
    virtual ~Model() = default;

private:
    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

    std::vector<Mesh> m_meshes;
    std::string m_directory;
    std::vector<aiString> m_loadedTextures;
};

