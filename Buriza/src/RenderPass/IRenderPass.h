#pragma once

#include <optional>
#include <variant>
#include <GLM/glm.hpp>
#include "../Util/Shader.h"

struct ShadowPassOutput;
struct CursorPassInput;

using IRenderPassOutput = std::variant<ShadowPassOutput, CursorPassInput>;

class IRenderPass
{
public:
    IRenderPass(Shader& shader)
        : m_shader(shader) 
    {}
    virtual IRenderPassOutput Run(std::optional<IRenderPassOutput> previousPassOutput) = 0;
    virtual ~IRenderPass() = default;

protected:
    Shader& m_shader;
};

struct ShadowPassOutput
{
    GLuint depthMapTexture;
    glm::mat4 lightSpaceMatrix;
};

struct CursorPassInput
{
    int x;
    int y;
};
