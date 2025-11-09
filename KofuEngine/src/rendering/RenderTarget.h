#pragma once
#include "buffers/FBO.h"

namespace RenderTarget
{
    FBO CreateSceneTarget(int width, int height);

    FBO CreateMSAATarget(int width, int height, int samples);

    FBO CreateShadowTarget(int width, int height);
}