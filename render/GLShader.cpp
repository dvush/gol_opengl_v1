//
// Created by dvu on 02.10.16.
//

#include <cstddef>
#include <iostream>
//#include <cstdlib>
#include "GLShader.h"
#include <fstream>
#include <streambuf>

void GLShader::loadFromString(const GLchar* source, GLShader::Type type)
{
    shaderHandle = 0;
    if(type == Type::fragment)
        shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
    if(type ==  Type::vertex)
        shaderHandle = glCreateShader(GL_VERTEX_SHADER);
    if(shaderHandle == 0)
        return;

    glShaderSource(shaderHandle,1, &source, NULL);
    glCompileShader(shaderHandle);

    GLint compiled;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1)
            {
            char* infoLog = new char[infoLen]; //(char*) malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shaderHandle, infoLen, NULL, infoLog);
            std::cout << "Error compiling shader " << infoLog << std::endl;
            delete[] infoLog;
        }
        glDeleteShader(shaderHandle);
    }
}

GLuint GLShader::getShaderHandle() const
{
    return shaderHandle;
}

GLShader::~GLShader()
{
    if(shaderHandle != 0)
        glDeleteShader(shaderHandle);
}

void GLShader::loadFromFile(const std::string &filename, GLShader::Type type)
{
    std::ifstream t(filename);
    if(!t.is_open()){
        std::cerr << "File not found: " << filename << std::endl;
    }
    std::basic_string<GLchar> str;
    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<GLchar>(t)),
            std::istreambuf_iterator<GLchar>());

    loadFromString(str.c_str(),type);
}
