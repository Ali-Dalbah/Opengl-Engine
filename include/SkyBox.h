#ifndef SKYBOX_H
#define SKYBOX_H
#include "Camera.h"
class SkyBox{
public:
    SkyBox(float, float, Shader*);
    void render(Camera&);
private:
    float width;
    float height;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int textures;
    Shader* shader;
};
#endif 