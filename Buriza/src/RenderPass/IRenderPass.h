#pragma once

#include <optional>
#include <string>
#include <variant>
#include <GLM/glm.hpp>
#include "../Util/Shader.h"

struct ShadowPassOutput;
struct CursorPassInput;
struct ConsolePassInput;

using IRenderPassOutput = std::variant<ShadowPassOutput, CursorPassInput, ConsolePassInput>;

class IRenderPass
{
public:
    IRenderPass(Shader& shader, GLuint width, GLuint height)
        : m_shader(shader) 
        , m_width(width)
        , m_height(height)
    {}
    virtual IRenderPassOutput Run(std::optional<IRenderPassOutput> previousPassOutput) = 0;
    virtual ~IRenderPass() = default;

protected:
    Shader& m_shader;
    int m_width;
    int m_height;
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

struct ConsolePassInput
{
    std::string text;
};
