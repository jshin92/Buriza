#pragma once

#include "IRenderPass.h"
#include "../Camera.h"

class DefaultPass : IRenderPass
{
public:
    DefaultPass(Shader& shader, Camera& camera);
    IRenderPassOutput Run(std::optional<IRenderPassOutput> previousPassOutput) override;
    ~DefaultPass() = default;

private:
    Camera& m_camera;
};

