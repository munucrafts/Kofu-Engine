#include "RenderTarget.h"

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
        FramebufferSpec specs;
        specs.width = width;
        specs.height = height;
        specs.hasColor = false;
        specs.hasDepth = true;
        specs.colorInternalFormat = GL_NONE;
        specs.depthInternalFormat = GL_DEPTH_COMPONENT32;
        fb.Init(specs);
        return fb;
    }
}