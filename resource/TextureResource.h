//
// Created by dvu on 23.10.16.
//

#ifndef WGV4_TEXTURE_H
#define WGV4_TEXTURE_H

class SDL_Surface;

class TextureResource {
public:
    TextureResource(const char * fileName);
    ~TextureResource();
    void insertBytesToBindedTexture();
    int getMode(){ return Mode; } // GL_{RGB,RGBA}
private:
    SDL_Surface* surface;
    int Mode;
};

#endif //WGV4_TEXTURE_H
