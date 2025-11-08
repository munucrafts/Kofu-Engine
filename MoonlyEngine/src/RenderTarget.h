#pragma once
#include "FBO.h"

namespace RenderTarget
{
    FBO CreateSceneTarget(int width, int height)
    {
        FBO fb;
        fb.Init({ width, height, true, true });
        return fb;
    }

    FBO CreateMSAATarget(int width, int height, int samples)
    {
        FBO fb;
        fb.Init({ width, height, true, true, samples });
        return fb;
    }

    FBO CreateShadowTarget(int width, int height)
    {
        FBO fb;
        FramebufferSpec s;
        s.width = width;
        s.height = height;
        s.hasColor = false;
        s.hasDepth = true;
        s.colorInternalFormat = GL_NONE;
        s.depthInternalFormat = GL_DEPTH_COMPONENT32;
        fb.Init(s);
        return fb;
    }
}