#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"
#include "Shader.h"

class Texture {
private:
    GLuint id;
public:
    const char* type;
    Texture(const char*,const char*,GLuint);
    void linkToShader(Shader&, const char*, GLuint);
    void bind();
    void unbind();
    void remove();
    ~Texture();
    unsigned int texNum;
};

#endif