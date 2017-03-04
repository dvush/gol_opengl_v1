//
// Created by dvu on 23.10.16.
//

#ifndef WGV4_GLTEXTURE_H
#define WGV4_GLTEXTURE_H

#include <SDL2/SDL_opengles2.h>
class TextureResource;

class GLTexture {
public:
    GLTexture();
    ~GLTexture();
    void initFromResource(TextureResource& resource);
    void initForFBOColorBuffer(int texWidth, int texHeight);
    void useTexture(GLenum position);
    GLuint getHandle(){ return textureHandle; }
private:
    void bind();
    GLuint textureHandle;
};

#endif //WGV4_GLTEXTURE_H
