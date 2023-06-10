#include "../include/Scene.h"

Scene::Scene(Camera* camera):
    camera(camera),
    sky(NULL), 
    components(), 
    buttons(),
    selected(NULL) {}

void Scene::render() {
    if (sky != NULL)
        sky->render(*camera);
    for (int i=0;i<components.size();i++)
        components[i]->render(*camera);
    for (int i=0;i<buttons.size();i++)
        buttons[i]->render();
}

void Scene::setCamera(Camera* camera) {
    Scene::camera = camera;
}

void Scene::removeComponent(int index) {
    components.erase(components.begin() + index);
}

void Scene::removeComponent(const std::string& name) {
    for (int i=0; i < components.size(); i++)
        if (!components[i]->name.compare(name))
            return removeComponent(i);
}

Component* Scene::getComponent(const std::string& name) {
    for (int i=0; i < components.size(); i++)
         if (!components[i]->name.compare(name))
            return components[i];
    return NULL;
}

void Scene::setButtonsShader(Shader& shader) {
    buttonsShader = &shader;
    assignShaderToButtons(shader);
}

void Scene::assignShaderToButtons(Shader& shader) {
    for (int i=0; i < buttons.size(); i++)
        buttons[i]->setShader(&shader);
}

void Scene::resizeCallBack(GLint width, GLint height) {
    glViewport(0, 0, width, height);
    camera->resize(width, height);
}

void Scene::scrollCallBack(double x, double y) {
	camera->scroll(y);
}

void Scene::processInput(GLFWwindow* window, double delta) {
    if (camera!=NULL)
    camera->processInput(window, delta);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        selected = NULL;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        x /= 800;
        y /= 600;
        if (!selected) selectItem(window, x, y);
        else {
            selected->move(x, y);
        }
    }
    for (int i=0;i<buttons.size();i++)
        if (buttons[i]->onClick(window, 800, 600))
            return;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_RELEASE) selected = NULL;
}

void Scene::addComponent(Component& component) {
    components.push_back(&component);
}

void Scene::addButton(Button2D& button) {
    buttons.push_back(&button);
    button.setShader(buttonsShader);
}

void Scene::setSkyBox(SkyBox& sky) {
    this->sky = &sky;
}

void Scene::selectItem(GLFWwindow* window, float x, float y) {
    std::vector<Button2D*>::iterator i = buttons.begin();
    std::vector<Button2D*>::iterator end = buttons.end();
    while (i != end) {
        Button2D* button = *i;
        if (button->isMouseOn(window, 800, 600)) return (void)(selected = button);
        i++;
    }
    selected = NULL;
}