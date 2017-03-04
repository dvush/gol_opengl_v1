//
// Created by dvu on 23.10.16.
//

#include "TextureResource.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengles2.h>

TextureResource::~TextureResource()
{
    if (surface!=nullptr) {
        SDL_FreeSurface(surface);
    }
}

TextureResource::TextureResource(const char* fileName)
{
    surface = IMG_Load(fileName);

    Mode = GL_RGB;
    if(surface->format->BytesPerPixel == 4) {
        Mode = GL_RGBA;
    }
}

void TextureResource::insertBytesToBindedTexture()
{
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
}

