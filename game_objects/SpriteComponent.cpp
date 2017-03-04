//
// Created by dvu on 28.10.16.
//

#include "SpriteComponent.h"
#include "../render/Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void SpriteComponent::prepareRenderCommand(Renderer &renderer) {
    /*glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
    glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
    glm::mat4 Model = Translate * Rotate * Scale;
*/

    modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
    modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position.x, position.y, 0.0f));
    glm::mat4& Model = modelMatrix;

    glm::vec4 bott_left = Model * glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f);
    glm::vec4 bott_right = Model * glm::vec4(1.0f, -1.0f, 0.0f, 1.0f);
    glm::vec4 top_left = Model * glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f);
    glm::vec4 top_right = Model * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);


    TriangleDrawCommand quadDrawtri1;
    quadDrawtri1.vertices[0] = {bott_right.x, bott_right.y,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 0.0f,};
    quadDrawtri1.vertices[1] = {bott_left.x, bott_left.y,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                0.0f, 0.0f,};
    quadDrawtri1.vertices[2] = {top_left.x, top_left.y,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                0.0f, 1.0f,};
    TriangleDrawCommand quadDrawtri2;
    quadDrawtri2.vertices[0] = quadDrawtri1.vertices[0];
    quadDrawtri2.vertices[1] = quadDrawtri1.vertices[2];
    quadDrawtri2.vertices[2] = {top_right.x, top_right.y,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f,};

    DrawInfo drawInfo1(z,textureHandle.id,shaderHandle.id,fboHandle.id,quadDrawtri1);
    DrawInfo drawInfo2(z,textureHandle.id,shaderHandle.id,fboHandle.id,quadDrawtri2);

    renderer.scheduleCommand(drawInfo1);
    renderer.scheduleCommand(drawInfo2);
}

SpriteComponent::SpriteComponent(const Vec2 position, float rotationAngle, float scale, int z,
                                 const ShaderHandle &shaderHandle, const TextureHandle &textureHandle,
                                 const FBOHandle &fboHandle) : position(position), rotationAngle(rotationAngle),
                                                               scale(scale), z(z), shaderHandle(shaderHandle),
                                                               textureHandle(textureHandle), fboHandle(fboHandle) {}
