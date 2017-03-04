//
// Created by dvu on 03.10.16.
//

#ifndef WGV4_RENDER_QUE_H
#define WGV4_RENDER_QUE_H

#include <SDL2/SDL_opengles2.h>
#include <map>
#include <vector>
#include "GLShaderProgram.h"
#include "GLTexture.h"
#include "../include/variant.h"
#include "GLFbo.h"
#include "DrawCommands.h"

class GLShaderProgram;


class RendererQue {
public:
    RendererQue();
    ~RendererQue();
    size_t getVertArrFree(){return (vertArrayMaxSize - vertArrayUsed); }
    int getIndexArrFree(){return (indexArrayMaxSize - indexArrayUsedSize); }
    void addBytesToVertArray(const void* pointer, const size_t size);
    void addArrayToIndexArray(const GLushort* array, const int size);
    GLushort getCurrentLastIndex(){ return indexArrayUsedSize;}
    void flushRenderQue(GLShaderProgram const& program);

private:
    unsigned char* vertArray;
    size_t vertArrayMaxSize; // in units of bytes
    size_t vertArrayUsed;
    GLushort* indexArray;
    int indexArrayMaxSize; // in units of "index count"
    int indexArrayUsedSize;
    GLuint VBOs[2];
};



#endif //WGV4_RENDER_QUE_H
