//
// Created by dvu on 02.10.16.
//

#ifndef WGV4_GLSHADER_H
#define WGV4_GLSHADER_H

#include <SDL2/SDL_opengles2.h>

class GLShader {
public:
    enum class Type{
        fragment, vertex
    };
    void loadFromFile(const std::string &filename, Type type);
    void loadFromString(const GLchar* source, Type type);
    GLuint getShaderHandle() const;
    ~GLShader();
private:
    GLuint shaderHandle;

};

#endif //WGV4_GLSHADER_H
