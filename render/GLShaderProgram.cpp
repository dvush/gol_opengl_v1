//
// Created by dvu on 02.10.16.
//

#include "GLShaderProgram.h"
#include "GLShader.h"
#include <cstddef>
#include <iostream>

void GLShaderProgram::loadFromFiles(const std::string &vertex, const std::string &fragment,
                                    std::vector<BindInfo> &bindInfo,
                                    std::vector<UniformInfo> &uniformInfo, GLenum elemType)
{
    GLShader vertexShader;
    vertexShader.loadFromFile(vertex, GLShader::Type::vertex);

    GLShader fragmentShader;
    fragmentShader.loadFromFile(fragment, GLShader::Type::fragment);

    createFromShaders(&vertexShader, &fragmentShader, bindInfo, uniformInfo, elemType);
}

void
GLShaderProgram::createFromSource(const GLchar* vertex, const GLchar* fragment, std::vector<BindInfo> bindInfo,
        std::vector<UniformInfo> uniformInfo, GLenum elemType)
{
    GLShader vertexShader;
    vertexShader.loadFromString(vertex, GLShader::Type::vertex);

    GLShader fragmentShader;
    fragmentShader.loadFromString(fragment, GLShader::Type::fragment);

    createFromShaders(&vertexShader, &fragmentShader, bindInfo, uniformInfo, elemType);
}

void GLShaderProgram::createFromShaders(GLShader *vertex, GLShader *fragment, const std::vector<BindInfo> &bindInfo,
                                        const std::vector<UniformInfo> &uniformInfo, GLenum elemType)
{
    shaderProgramHandle = glCreateProgram();
    glAttachShader(shaderProgramHandle, vertex->getShaderHandle());
    glAttachShader(shaderProgramHandle, fragment->getShaderHandle());
    for (auto& bindAttrInfo : bindInfo) {
        glBindAttribLocation(shaderProgramHandle, bindAttrInfo.index, bindAttrInfo.name.c_str());
        vertexSize += bindAttrInfo.size;
    }
    glLinkProgram(shaderProgramHandle);

    GLint linked;
    glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(shaderProgramHandle, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen>1) {
            char* infoLog = new char[infoLen];
            glGetProgramInfoLog(shaderProgramHandle, infoLen, NULL, infoLog);
            std::cout << "Error linking shader: " << infoLog << std::endl;
            delete[] infoLog;
        }
        glDeleteProgram(shaderProgramHandle);
        return;
    }

    glUseProgram(shaderProgramHandle);
    for (auto& uniformInfoVal : uniformInfo) {
        uniforms.emplace(std::piecewise_construct, std::forward_as_tuple(uniformInfoVal.name),
                std::forward_as_tuple());
        uniforms[uniformInfoVal.name].location = glGetUniformLocation(shaderProgramHandle, uniformInfoVal.name.c_str());
        uniforms[uniformInfoVal.name].value = uniformInfoVal.defaultValue;
    }

    attributeInfo = bindInfo;
    elementsType = elemType;
}

GLuint GLShaderProgram::getShaderProgramHandle() const
{
    return shaderProgramHandle;
}

GLShaderProgram::~GLShaderProgram()
{
    if (shaderProgramHandle!=0)
        glDeleteProgram(shaderProgramHandle);
}

void GLShaderProgram::setAttribPointerForVBO() const
{
    size_t offset = 0;
    for (auto& autoInfo : attributeInfo) {
        glEnableVertexAttribArray(autoInfo.index);
        glVertexAttribPointer(autoInfo.index, autoInfo.size, GL_FLOAT, false, vertexSize*sizeof(GLfloat),
                (const void*) offset);
        offset += autoInfo.size*sizeof(GLfloat);
    }
}

class UniformValueVisitor {
public:
    static UniformValueVisitor instance;
    int location;

    void operator()(const float& val) const
    {
        glUniform1f(location, val);
    }

    void operator()(const int& val) const
    {
        glUniform1i(location, val);
    }

    void operator()(const std::vector<float>& val) const
    {
        glUniform4fv(location, val.size(), &val[0]);
    }

    void operator()(const std::vector<int>& val) const
    {
        glUniform4iv(location, val.size(), &val[0]);
    }
};

UniformValueVisitor UniformValueVisitor::instance = UniformValueVisitor();

void GLShaderProgram::setupUniforms() const
{
    const UniformValueVisitor visitor{};
    for (auto& uniformMapPair : uniforms) {
        auto& uniform = uniformMapPair.second;
        UniformValueVisitor::instance.location = uniform.location;
        apply_visitor(UniformValueVisitor::instance, uniform.value);
    }
}

void GLShaderProgram::setUniformValue(std::string& name, uniformValue value)
{
    uniforms[name].value = value;
}
void GLShaderProgram::setUniformValue(const char *name, uniformValue value) {
    std::string tmp(name);
    setUniformValue(tmp,value);
}

void GLShaderProgram::useProgram() const
{
    glUseProgram(shaderProgramHandle);
    setupUniforms();
}



