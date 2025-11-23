#include "RenderTarget.h"

namespace RenderTarget
{
    FBO CreateSceneTarget(int width, int height)
    {
        FBO fb;
        fb.Init({ .width = width, .height = height, .hasColor = true, .hasDepth = true });
        return fb;
    }

    FBO CreateMSAATarget(int width, int height, int samples)
    {
        FBO fb;
        fb.Init({ .width = width, .height = height, .samples = samples, .hasColor = true, .hasDepth = true });
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
        specs.depthAsTexture = true;
        specs.depthCube = false;
        fb.Init(specs);
        return fb;
    }

    FBO CreateCubemapTarget(int width, int height)
    {
        FBO fb;
        FramebufferSpec specs;
        specs.width = width;
        specs.height = height;
        specs.hasColor = false;
        specs.hasDepth = true;
        specs.depthAsTexture = true;
        specs.depthCube = true;
        fb.Init(specs);
        return fb;
    }
}