#ifndef BUTTON2D_H
#define BUTTON2D_H
#include "Model.h"
#include "Rect.h"
class Button2D {
public:
    Button2D(float,float,float,float,void(*)(void));
    bool onClick(GLFWwindow*,int,int);
    void setShader(Shader*);
    void render();
    void translate(float, axis);
    void move(float, float);
    bool isMouseOn(GLFWwindow*,int,int);
    ~Button2D();
private:
    Shader* buttonsShader;
    Rect rect;
    double coolDown;
    float width;
    float height;
    float xpos;
    float ypos;
    void (*func)(void);
};
#endif