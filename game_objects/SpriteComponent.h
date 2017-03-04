//
// Created by dvu on 28.10.16.
//

#ifndef WGV4_SPRITECOMPONENT_H
#define WGV4_SPRITECOMPONENT_H


#include "../render/RenderResources.h"
#include "../render/DrawCommands.h"
#include "../common/Vectors.h"

class Renderer;

class SpriteComponent {
public:
    void prepareRenderCommand(Renderer &renderer);

    SpriteComponent(const Vec2 position, float rotationAngle, float scale, int z, const ShaderHandle &shaderHandle,
                    const TextureHandle &textureHandle, const FBOHandle &fboHandle);

//private:
    Vec2 position;
    float rotationAngle;
    float scale;
    int z;

    ShaderHandle shaderHandle;
    TextureHandle textureHandle;
    FBOHandle fboHandle;

    glm::mat4 modelMatrix;

};


#endif //WGV4_SPRITECOMPONENT_H
