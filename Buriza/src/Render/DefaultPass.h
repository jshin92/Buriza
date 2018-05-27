#pragma once

#include "IRenderPass.h"
#include "../Camera.h"

class DefaultPass : IRenderPass
{
public:
    DefaultPass(Shader& shader, Camera& camera);
    RenderPassOutput Run(std::optional<RenderPassOutput> previousPassOutput) override;
    ~DefaultPass() = default;

private:
    Camera& m_camera;
};

