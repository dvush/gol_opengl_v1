//
// Created by dvu on 23.10.16.
//

#include "RenderResourceManager.h"
#include "../resource/TextureResource.h"

void RenderResourceManager::loadResource(ShaderDescription shaderResource)
{
    int id = shaders.size();
    shaders.emplace_back();
    shaders.back().loadFromFiles(shaderResource.vertShaderFile, shaderResource.fragSourceFile, shaderResource.bindInfo,
            shaderResource.uniformInfo, shaderResource.elementType);

    ShaderHandle shaderHandle(id, &shaders[id]);
    shaderNameTable[shaderResource.name] = shaderHandle;
}

void RenderResourceManager::loadResource(FboDescription fboResource)
{
    int fboID = fbos.size();
    fbos.emplace_back();
    GLFbo& fbo = fbos.back();

    int textureID = textures.size();
    textures.emplace_back();
    GLTexture& texture = textures.back();

    texture.initForFBOColorBuffer(fboResource.width,fboResource.height);

    fbo.useTextureAsColorBuffer(texture);
    fbo.setupDepthBuffer(fboResource.width, fboResource.height);

    FBOHandle fboHandle(fboID, &fbos[fboID]);
    fbosNameTable[fboResource.name] = fboHandle;

    TextureHandle textureHandle(textureID, &textures[textureID]);
    textureNameTable[fboResource.textureName] = textureHandle;
    /*
    fbosNameTable.emplace(std::piecewise_construct,
            std::forward_as_tuple(fboResource.name),
            std::forward_as_tuple(fboID,fbos[fboID]));
    textureNameTable.emplace(std::piecewise_construct,
            std::forward_as_tuple(fboResource.textureName),
            std::forward_as_tuple(textureID, textures[textureID]));
            */

}

void RenderResourceManager::loadResource(TextureDescription textureDescription)
{
    int textureID = textures.size();
    textures.emplace_back();
    GLTexture& texture = textures.back();
    TextureResource resource(textureDescription.fileName.c_str());
    texture.initFromResource(resource);

    TextureHandle textureHandle(textureID, &textures[textureID]);
    textureNameTable[textureDescription.name] = textureHandle;
    /*
    textureNameTable.emplace(std::piecewise_construct,
            std::forward_as_tuple(textureDescription.name),
            std::forward_as_tuple(textureID, textures[textureID])); */
}

ShaderHandle RenderResourceManager::getShaderHandle(const char* name)
{
    return shaderNameTable.at(name);
}

TextureHandle RenderResourceManager::getTextureHandle(const char* name)
{
    return textureNameTable.at(name);
}

FBOHandle RenderResourceManager::getFBOhandle(const char* name)
{
    return fbosNameTable.at(name);
}

RenderResourceManager::RenderResourceManager() {
    //FIXME: fix critical issue: pointer to objects stored in vec could be invalidated
    textures.reserve(5);
    fbos.reserve(5);
    shaders.reserve(5);

    fbos.emplace_back(); //fbo 0 - screen
    FBOHandle fboHandle(0, &fbos[0]);
    fbosNameTable["screen"] = fboHandle;
}
