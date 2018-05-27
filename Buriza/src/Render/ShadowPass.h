#pragma once

#include "IRenderPass.h"

class ShadowPass : public IRenderPass
{
public:
    ShadowPass(Shader& shader);
    RenderPassOutput Run(std::optional<RenderPassOutput> previousPassOutput) override;
    ~ShadowPass() = default;

private:
    GLuint m_depthMapFBO;
    GLuint m_depthMapTexture;
    GLuint m_shadowWidth;
    GLuint m_shadowHeight;
};

