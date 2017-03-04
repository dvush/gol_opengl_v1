//
// Created by dvu on 23.10.16.
//

#include "Renderer.h"
#include "GLShaderProgram.h"
#include "../resource/TextureResource.h"
#include "GLTexture.h"
#include "GLFbo.h"
#include <SDL2/SDL_opengles2.h>
#include <algorithm>

Renderer::Renderer()
{
    drawCommandVisitor.rendererQue = &rendererQue;
}

void Renderer::renderScheduledCommands()
{
    sortRenderQue();

    for (int i = 0; i<resourceManager.fbos.size(); ++i) {
        if (i!=0) {
            resourceManager.fbos[i].clear();
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (drawCommands.size()>0)
        prepareStateForFirstCommand(drawCommands[0]);

    for (auto& command : drawCommands) {
        if (command.targetFBO!=currentFBO) {
            flush();
            currentFBO = command.targetFBO;
            if (currentFBO==0) {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
            else {
                resourceManager.fbos[currentFBO].bind();
            }
        }
        if (command.shaderID!=currentShader) {
            flush();
            currentShader = command.shaderID;
            resourceManager.shaders[currentShader].useProgram();
            drawCommandVisitor.currentProgram = &resourceManager.shaders[currentShader];
        }
        if (command.mainTextureID!=currentTexture) {
            flush();
            currentTexture = command.mainTextureID;
            resourceManager.textures[currentTexture].useTexture(GL_TEXTURE0);
        }

        apply_visitor(drawCommandVisitor, command.command);
    }

    flush();
    drawCommands.clear();
}

void Renderer::sortRenderQue()
{
    std::sort(drawCommands.begin(), drawCommands.end(),
            [](const DrawInfo& A, const DrawInfo& B) {
                return A.targetFBO>B.targetFBO;
            });

    std::stable_sort(drawCommands.begin(), drawCommands.end(),
            [](const DrawInfo& A, const DrawInfo& B) {
                return (A.targetFBO==B.targetFBO) && (A.zOrder<B.zOrder);
            });

    std::stable_sort(drawCommands.begin(), drawCommands.end(),
            [](const DrawInfo& A, const DrawInfo& B) {
                return (A.targetFBO==B.targetFBO) && (A.zOrder==B.zOrder) && (A.shaderID<B.shaderID);
            });
    std::stable_sort(drawCommands.begin(), drawCommands.end(),
            [](const DrawInfo& A, const DrawInfo& B) {
                return (A.targetFBO==B.targetFBO) && (A.zOrder==B.zOrder) && (A.shaderID==B.shaderID)
                        && (A.mainTextureID<B.mainTextureID);
            });
}

void Renderer::prepareStateForFirstCommand(DrawInfo& drawInfo)
{
    currentFBO = drawInfo.targetFBO;
    if (currentFBO==0) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else {
        resourceManager.fbos[currentFBO].bind();
    }

    currentTexture = drawInfo.mainTextureID;
    resourceManager.textures[currentTexture].useTexture(GL_TEXTURE0);

    currentShader = drawInfo.shaderID;
    resourceManager.shaders[currentShader].useProgram();
    drawCommandVisitor.currentProgram = &resourceManager.shaders[currentShader];
}

void Renderer::flush()
{
    rendererQue.flushRenderQue(resourceManager.shaders[currentShader]);
}

void DrawCommandVisitor::operator()(const TriangleDrawCommand& triComm)
{
    size_t size = sizeof(triComm.vertices);
    int indSize = 3;

    if (rendererQue->getIndexArrFree()<indSize || rendererQue->getVertArrFree()<size) {
        rendererQue->flushRenderQue(*currentProgram);
    }

    GLushort indexArray[3];
    GLushort lastIndex = rendererQue->getCurrentLastIndex();
    indexArray[0] = lastIndex+0;
    indexArray[1] = lastIndex+1;
    indexArray[2] = lastIndex+2;
    rendererQue->addArrayToIndexArray(indexArray, 3);

    rendererQue->addBytesToVertArray(&triComm.vertices[0], size);

}
