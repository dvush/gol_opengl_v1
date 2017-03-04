//
// Created by dvu on 28.10.16.
//

#ifndef WGV4_DRAWCOMMANDS_H
#define WGV4_DRAWCOMMANDS_H

#include <SDL2/SDL_opengles2.h>
#include "../include/variant.h"

struct TriangleDrawCommand {

    struct Vertex_XY_RGBA_UV {
        GLfloat vertexData[8];
    };
    Vertex_XY_RGBA_UV vertices[3];
};



using DrawCommand = variant<TriangleDrawCommand>;

struct DrawInfo {
    int zOrder;
    int mainTextureID;
    int shaderID;
    int targetFBO;
    DrawCommand command;

    DrawInfo(int zOrder, int mainTextureID, int shaderID, int targetFBO, const DrawCommand &command) : zOrder(zOrder),
                                                                                                       mainTextureID(
                                                                                                               mainTextureID),
                                                                                                       shaderID(
                                                                                                               shaderID),
                                                                                                       targetFBO(
                                                                                                               targetFBO),
                                                                                                       command(command) {}
};

#endif //WGV4_DRAWCOMMANDS_H
