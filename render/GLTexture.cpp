//
// Created by dvu on 23.10.16.
//

#include "GLTexture.h"
#include "../resource/TextureResource.h"

GLTexture::GLTexture()
{
    glGenTextures(1, &textureHandle);
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1, &textureHandle);
}

void GLTexture::bind()
{
    glBindTexture(GL_TEXTURE_2D, textureHandle);
}

void GLTexture::initFromResource(TextureResource& resource)
{
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    bind();
    resource.insertBytesToBindedTexture();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void GLTexture::useTexture(GLenum position)
{
    glActiveTexture(position);
    bind();
}

void GLTexture::initForFBOColorBuffer(int texWidth, int texHeight)
{
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

