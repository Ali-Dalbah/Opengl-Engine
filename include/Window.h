#ifndef WINDOW_H
#define WINDOW_H

#include "Model.h"
#include "Button2D.h"
#include "Scene.h"

class Window {
public:
    Window(GLint, GLint, const std::string);
    void render();
    void setScene(Scene&);
    bool shouldClose();
    std::string title;
    void setTitle(const std::string&);
    void setScrollCallBack(void(*)(GLFWwindow*, double, double));
    void setResizeCallBack(void(*)(GLFWwindow*, GLint, GLint));
    void processInput(double);
    ~Window();
    void atLoopEnd();
    void setKeyFunc(void(*)(GLFWwindow*));
    static void initGl();
private:
    Scene* scene;
    GLint width;
    GLFWwindow* window;
    GLint height;
    SkyBox* sky;
    void (*customKeyFunc)(GLFWwindow*);
};

#endif