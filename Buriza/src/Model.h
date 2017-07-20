#pragma once

#include <vector>
#include <ASSIMP/material.h>
#include "Mesh.h"
#include "Shader.h"

class aiMesh;
class aiNode;
class aiScene;

class Model
{
public:
    Model(const char* path);
    void Draw(const Shader& shader);
    virtual ~Model() = default;

private:
    void LoadModel(const char* path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};

