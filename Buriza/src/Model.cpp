#include <iostream>
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/postprocess.h>
#include <SOIL/SOIL.h>
#include "Model.h"

namespace
{
    GLuint TextureFromFile(const char* path, const std::string& directory, bool gamma=false);
}

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
    for (GLuint i = 0; i < node->mNumMeshes; ++i)
    {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.emplace_back(ProcessMesh(mesh, scene));
    }

    for (GLuint i = 0; i < node->mNumChildren; ++i)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices{};
    std::vector<GLuint> indices{};
    std::vector<Texture> textures{};

    // Vertices
    for (GLuint i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex{};
        // process vertex positions
        glm::vec3 vector{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.Position = vector;

        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        // texture coordinates
        glm::vec2 vec{0.0f, 0.0f};
        if (mesh->mTextureCoords[0])
        {
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
        }
        vertex.TexCoords = vec;

        vertices.emplace_back(vertex);
    }

    // Indices
    for (GLuint i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; ++j)
        {
            indices.emplace_back(face.mIndices[j]);
        }
    }

    // Materials
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
    std::vector<Texture> textures{};
    for (GLuint i = 0; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        if (std::find(m_loadedTextures.begin(), m_loadedTextures.end(), str) != m_loadedTextures.end()) continue;

        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), m_directory);
        texture.type = typeName;
        texture.path = str;
        textures.emplace_back(texture);

        m_loadedTextures.emplace_back(str);
    }
    return textures;
}

namespace
{
    GLuint TextureFromFile(const char* path, const std::string& directory, bool gamma)
    {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        GLuint textureID;
        glGenTextures(1, &textureID);

        GLint width, height;//, numComponents;
        //GLubyte* data = stbi_load(filename.c_str(), &width, &height, &numComponents, 0);
        GLubyte* data = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        if (data)
        {
            GLenum format = GL_RGB;
            /*
            GLenum format;
            if (numComponents == 1) format = GL_RED;
            else if (numComponents == 3) format = GL_RGB;
            else if (numComponents == 4) format = GL_RGBA;
            else std::cerr << "Unmatched numComponents: " << numComponents << std::endl;
            */
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            std::cerr << "Texture failed to load at path: " << path << std::endl;
        }
        //stbi_image_free(data);
        SOIL_free_image_data(data);
        return textureID;
    }
}
