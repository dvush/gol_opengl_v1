//
// Created by dvu on 02.10.16.
//

#ifndef WGV4_GLSHADERPROGRAM_H
#define WGV4_GLSHADERPROGRAM_H

#include <SDL2/SDL_opengles2.h>
#include <string>
#include <vector>
#include <map>

#include <glm/mat4x4.hpp>
#include <memory>

#include "../include/variant.h"

using uniformValue = variant<float, int, std::vector<float>, std::vector<int>>;

struct Uniform{
    int location;
    uniformValue value;
};


struct UniformInfo{
    std::string name;
    uniformValue defaultValue;

    //UniformInfo(const char* name) : name{name} {};
    UniformInfo(const char* name, uniformValue defaultValue) : name{name}, defaultValue{defaultValue} {};
};

class GLShader;

struct BindInfo {
    GLuint index;
    GLint size; // for x, y, z : size = 3
    std::basic_string<GLchar> name;

    BindInfo(GLuint index, GLint size, const GLchar* name)
            :index{index}, size{size}, name{name} { };
};

class GLShaderProgram {
public:
    void createFromShaders(GLShader *vertex, GLShader *fragment, const std::vector<BindInfo> &bindInfo,
                           const std::vector<UniformInfo> &uniformInfo, GLenum elemType);

    void
    createFromSource(const GLchar* vertex, const GLchar* fragment, std::vector<BindInfo> bindInfo,
            std::vector<UniformInfo> uniformInfo, GLenum elemType);

    void loadFromFiles(const std::string &vertex, const std::string &fragment, std::vector<BindInfo> &bindInfo,
                       std::vector<UniformInfo> &uniformInfo, GLenum elemType);

    GLuint getShaderProgramHandle() const;

    void useProgram() const;

    void setAttribPointerForVBO() const;

    GLint getAttributeLocation(const GLchar* name) const { return glGetAttribLocation(shaderProgramHandle, name); }

    GLint getUniformLocation(const GLchar* name) const { return glGetUniformLocation(shaderProgramHandle, name); }

    GLenum getElementsType() const { return elementsType; }

    ~GLShaderProgram();

    void setUniformValue(std::string& name, uniformValue value);
    void setUniformValue(const char * name, uniformValue value);

private:
    void setupUniforms() const;

    GLuint shaderProgramHandle;
    GLenum elementsType;
    GLint vertexSize; //in units size of float
    std::vector<BindInfo> attributeInfo;
    std::map<std::string, Uniform> uniforms;
};

#endif //WGV4_GLSHADERPROGRAM_H
