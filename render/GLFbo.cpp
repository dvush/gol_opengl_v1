//
// Created by dvu on 23.10.16.
//

#include "GLFbo.h"

GLFbo::GLFbo() {
    glGenFramebuffers(1,&fboHandle);
    glGenRenderbuffers(1,&depthBufferHandle);
}

GLFbo::~GLFbo()
{
    glDeleteRenderbuffers(1,&depthBufferHandle);
    glDeleteFramebuffers(1,&fboHandle);
}

void GLFbo::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

}

void GLFbo::useTextureAsColorBuffer(GLTexture& texture)
{
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getHandle(), 0);
}

void GLFbo::setupDepthBuffer(int texWidth, int texHeight)
{
    bind();
    glBindRenderbuffer(GL_RENDERBUFFER, depthBufferHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16,
            texWidth, texHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
            GL_RENDERBUFFER, depthBufferHandle);
}

void GLFbo::clear()
{
    bind();
    glClearColor(0.3f,0.3f,0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
