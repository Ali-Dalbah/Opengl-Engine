#ifndef SCENE_H
#define SCENE_H
#include "Component.h"
#include "SkyBox.h"
#include "Button2D.h"
class Scene {
public:
    Scene(Camera*);
    void render();
    void addComponent(Component&);
    void addButton(Button2D&);
    Component* getComponent(const std::string&);
    void removeComponent(int);
    void removeComponent(const std::string&);
    void setCamera(Camera*);
    void setButtonsShader(Shader&);
    void resizeCallBack(GLint, GLint);
    void processInput(GLFWwindow*, double);
    void scrollCallBack(double, double);
    void setSkyBox(SkyBox&);
    void selectItem(GLFWwindow*, float, float);
private:
    void assignShaderToButtons(Shader& shader);
    Camera* camera;
    std::vector<Component*> components;
    std::vector<Button2D*> buttons;
    Shader* buttonsShader;
    SkyBox* sky;
    Button2D* selected;
};

#endif