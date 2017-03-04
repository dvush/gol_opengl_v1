//
// Created by dvu on 03.10.16.
//

#include "RendererQue.h"
#include "../resource/TextureResource.h"
#include <algorithm>
#include <cstring>
#include <iostream>

RendererQue::RendererQue()
{
    int vertMaxCount = 65000; //arbitrary number
    vertArray = new unsigned char[vertMaxCount];
    vertArrayMaxSize = vertMaxCount*sizeof(unsigned char);
    vertArrayUsed = 0;

    int indexArrayCount = 10000;
    indexArray = new GLushort[indexArrayCount];
    indexArrayMaxSize = indexArrayCount*sizeof(GLushort);
    indexArrayUsedSize = 0;

    glGenBuffers(2, VBOs);
}

RendererQue::~RendererQue()
{
    glDeleteBuffers(2, VBOs);

    delete[] vertArray;
    delete[] indexArray;
}

void RendererQue::flushRenderQue(GLShaderProgram const& program)
{
    if(indexArrayUsedSize==0)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, vertArrayUsed, vertArray, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArrayUsedSize*sizeof(GLushort), indexArray, GL_DYNAMIC_DRAW);

    program.setAttribPointerForVBO();

    glDrawElements(program.getElementsType(), indexArrayUsedSize, GL_UNSIGNED_SHORT, 0);

    vertArrayUsed = 0;
    indexArrayUsedSize = 0;
}

void RendererQue::addBytesToVertArray(const void* pointer, const size_t size)
{
    memcpy(vertArray+vertArrayUsed, pointer, size);
    vertArrayUsed += size;
}

void RendererQue::addArrayToIndexArray(const GLushort* array, const int size)
{
    memcpy(indexArray+indexArrayUsedSize, array, size*sizeof(GLushort));
    indexArrayUsedSize += size;
}
