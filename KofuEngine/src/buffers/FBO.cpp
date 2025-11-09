#include "buffers/FBO.h"

void FBO::Init(const FramebufferSpec& specData)
{
    spec = specData;
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    if (spec.hasColor)
    {
        glGenTextures(1, &colorTex);

        if (spec.samples > 1)
        {
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorTex);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, spec.samples, spec.colorInternalFormat, spec.width, spec.height, GL_TRUE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, colorTex, 0);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, colorTex);
            glTexImage2D(GL_TEXTURE_2D, 0, spec.colorInternalFormat, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTex, 0);
        }
    }

    if (spec.hasDepth)
    {
        glGenRenderbuffers(1, &depthRBO);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);

        if (spec.samples > 0)
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, spec.samples, spec.depthInternalFormat, spec.width, spec.height);
        else
            glRenderbufferStorage(GL_RENDERBUFFER, spec.depthInternalFormat, spec.width, spec.height);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRBO);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("FBO not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Resize(int width, int height)
{
    spec.width = width;
    spec.height = height;
    Init(spec);
}

void FBO::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FBO::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Delete()
{
    glDeleteFramebuffers(1, &id);
    glDeleteTextures(1, &colorTex);
    glDeleteRenderbuffers(1, &depthRBO);
}