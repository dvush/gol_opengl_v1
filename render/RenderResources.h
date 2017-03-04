//
// Created by dvu on 25.10.16.
//

#ifndef WGV4_RENDERRESOURCES_H
#define WGV4_RENDERRESOURCES_H

#include "GLShaderProgram.h"

class GLShaderProgram;

class GLTexture;

class GLFbo;

template<typename T>
struct Handle {
    int id;
    T *obj;

    Handle() : id{-1}, obj{nullptr} {};

    Handle(int id, T *t) : id{id}, obj{t} {};
};

using ShaderHandle = Handle<GLShaderProgram>;
using TextureHandle = Handle<GLTexture>;
using FBOHandle = Handle<GLFbo>;

struct ShaderDescription {
    std::string name;
    std::string vertShaderFile;
    std::string fragSourceFile;
    std::vector<BindInfo> bindInfo;
    std::vector<UniformInfo> uniformInfo;
    GLenum elementType;

    ShaderDescription(const char * name, const char * vertShaderFile, const char * fragSourceFile,
                      const std::vector<BindInfo> bindInfo, const std::vector<UniformInfo> uniformInfo,
                      GLenum elementType) : name(name), vertShaderFile(vertShaderFile), fragSourceFile(fragSourceFile),
                                            bindInfo(bindInfo), uniformInfo(uniformInfo), elementType(elementType) {}
};

struct TextureDescription {
    std::string name;
    std::string fileName;

    TextureDescription(const char * name, const char * fileName) : name{name}, fileName{fileName} {}
};

struct FboDescription {
    std::string name;
    std::string textureName;
    int width, height;

    FboDescription(const char * name, const char * textureName, int width, int height) : name(name),
                                                                                                     textureName(
                                                                                                             textureName),
                                                                                                     width(width),
                                                                                                     height(height) {}
};
#endif //WGV4_RENDERRESOURCES_H
