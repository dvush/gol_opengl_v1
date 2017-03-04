//
// Created by dvu on 23.10.16.
//

#ifndef WGV4_RENDERRESOURCEMANAGER_H
#define WGV4_RENDERRESOURCEMANAGER_H

#include "GLShaderProgram.h"
#include "GLTexture.h"
#include "GLFbo.h"

#include "RenderResources.h"

class RenderResourceManager {
public:
    friend class Renderer;

    RenderResourceManager();

    void loadResource(ShaderDescription shaderResource);
    void loadResource(FboDescription fboResource);
    void loadResource(TextureDescription textureResource);

    ShaderHandle getShaderHandle(const char* name);
    TextureHandle getTextureHandle(const char* name);
    FBOHandle getFBOhandle(const char* name);
private:
    std::map<std::string,ShaderHandle> shaderNameTable;
    std::vector<GLShaderProgram> shaders;

    std::map<std::string,TextureHandle> textureNameTable;
    std::vector<GLTexture> textures;

    std::map<std::string,FBOHandle> fbosNameTable;

    //TODO: debug
public:
    std::vector<GLFbo> fbos;
};

#endif //WGV4_RENDERRESOURCEMANAGER_H
