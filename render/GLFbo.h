//
// Created by dvu on 23.10.16.
//

#ifndef WGV4_GLFBO_H
#define WGV4_GLFBO_H

#include <SDL2/SDL_opengles2.h>
#include "GLTexture.h"

class GLFbo {
public:
    GLFbo();

    virtual ~GLFbo();

    void useTextureAsColorBuffer(GLTexture& texture);
    void setupDepthBuffer(int texWidth, int texHeight);
    void bind();
    void clear();
private:
    GLuint fboHandle;
    GLuint depthBufferHandle;
};

#endif //WGV4_GLFBO_H
