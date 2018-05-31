#pragma once

#include "IRenderPass.h"

class ShadowPass : public IRenderPass
{
public:
    ShadowPass(Shader& shader, int width, int height);
    IRenderPassOutput Run(std::optional<IRenderPassOutput> previousPassOutput) override;
    ~ShadowPass() = default;

private:
    GLuint m_depthMapFBO;
    GLuint m_depthMapTexture;
};

