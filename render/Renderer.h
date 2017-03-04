//
// Created by dvu on 23.10.16.
//

#ifndef WGV4_RENDERER_H
#define WGV4_RENDERER_H

#include "RendererQue.h"
#include "RenderResourceManager.h"
#include <map>

class GLFbo;

class GLTexture;

class GLShaderProgram;

class DrawCommandVisitor {
public:
    RendererQue *rendererQue;
    GLShaderProgram *currentProgram;

    void operator()(const TriangleDrawCommand &triComm);
};

/*
 * Stores shaders, handles drawingQue
 */
class Renderer {
public:
    Renderer();

    //void addDrawCommand(TriangleDrawInfo triangleDrawInfo);
    void renderScheduledCommands();

    void scheduleCommand(DrawInfo command) { drawCommands.push_back(command); }

    RenderResourceManager &getResourceManager() { return resourceManager; }

private:
    std::vector<DrawInfo> drawCommands;
    RendererQue rendererQue;
    RenderResourceManager resourceManager;

    void flush();

    void sortRenderQue();

    void prepareStateForFirstCommand(DrawInfo &drawInfo);

    DrawCommandVisitor drawCommandVisitor;

    int currentFBO;
    int currentTexture;
    int currentShader;
};

#endif //WGV4_RENDERER_H
