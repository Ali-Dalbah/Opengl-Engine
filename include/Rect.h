#ifndef RECT_H
#define RECT_H
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
class Rect{
    public:
        VAO vao;
        Rect(float, float);
        void render();
};
#endif