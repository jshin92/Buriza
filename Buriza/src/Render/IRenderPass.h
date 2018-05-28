#pragma once

#include <optional>
#include <GLM/glm.hpp>
#include "../Util/Shader.h"

struct RenderPassOutput
{
    GLuint depthMapTexture;
    glm::mat4 lightSpaceMatrix;
};

class IRenderPass
{
public:
    IRenderPass(Shader& shader)
        : m_shader(shader) 
    {}
    virtual RenderPassOutput Run(std::optional<RenderPassOutput> previousPassOutput) = 0;
    virtual ~IRenderPass() = default;

protected:
    Shader& m_shader;
};