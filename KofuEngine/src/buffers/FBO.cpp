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
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, spec.samples, GL_RGBA, spec.width, spec.height, GL_TRUE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, colorTex, 0);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, colorTex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTex, 0);
        }
    }

    if (spec.hasDepth)
    {
        if (spec.depthAsTexture)
        {
            glGenTextures(1, &depthTex);
            glBindTexture(GL_TEXTURE_2D, depthTex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, spec.width, spec.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

            float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
            glBindFramebuffer(GL_FRAMEBUFFER, depthTex);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

            if (!spec.hasColor)
            {
                glDrawBuffer(GL_NONE);
                glReadBuffer(GL_NONE);
            }
        }
        else if (spec.depthCube)
        {
            glGenTextures(1, &depthTex);
            glBindTexture(GL_TEXTURE_CUBE_MAP, depthTex);

            for (unsigned int i = 0; i < 6; i++)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, spec.width, spec.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            }

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            if (!spec.hasColor)
            {
                glDrawBuffer(GL_NONE);
                glReadBuffer(GL_NONE);
            }
        }
        else
        {
            glGenRenderbuffers(1, &depthRBO);
            glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);

            if (spec.samples > 1)
            {
                glRenderbufferStorageMultisample(GL_RENDERBUFFER, spec.samples, GL_DEPTH24_STENCIL8, spec.width, spec.height);
            }
            else
            {
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, spec.width, spec.height);
            }

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRBO);
        }
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("FBO not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Resize(const int width, const int height)
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
    glDeleteTextures(1, &depthTex);
    glDeleteRenderbuffers(1, &depthRBO);
}