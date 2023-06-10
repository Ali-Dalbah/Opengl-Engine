#include "../include/Button2D.h"

Button2D::Button2D(float width, float height, float xpos, float ypos, void(*func)(void)):
    rect(width, height),
    func(func),
    width(width),
    height(height),
    xpos(xpos),
    ypos(ypos),
    coolDown(0) {}

Button2D::~Button2D() {}

void Button2D::setShader(Shader* buttonsShader) {
    Button2D::buttonsShader = buttonsShader;
    buttonsShader->activate();
    glUniform1i(glGetUniformLocation(buttonsShader->getId(), "mouseOn"), 0);
    glUniform2fv(glGetUniformLocation(buttonsShader->getId(), "displacement"), 1, glm::value_ptr(glm::vec2(xpos * 2, -ypos * 2)));
    glUniform3fv(glGetUniformLocation(buttonsShader->getId(), "buttonColor"), 1, glm::value_ptr(glm::vec3(1, 0, 1)));
}

void Button2D::render() {
    if (!buttonsShader) return ;
    buttonsShader->activate();
    rect.render();
}

bool Button2D::isMouseOn(GLFWwindow* window, int wWidth, int wHeight) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    xpos = xpos/wWidth;
    ypos = ypos/wHeight;
    if (xpos > 1 || ypos > 1 || xpos < 0 || ypos < 0) return false;
    //std::cout << "xpos " << xpos << "ypos " << ypos << std::endl;
    if (xpos < this->xpos + width/2 && xpos > this->xpos - width/2 && ypos < this->ypos + height/2 && ypos > this->ypos - height/2){
        if (buttonsShader != NULL) glUniform1i(glGetUniformLocation(buttonsShader->getId(), "mouseOn"), 1);
        return true;
    }
    if (buttonsShader != NULL) glUniform1i(glGetUniformLocation(buttonsShader->getId(), "mouseOn"), 0);
    return false;
}

bool Button2D::onClick(GLFWwindow* window, int wWidth, int wHeight) {
    if (!isMouseOn(window, wWidth, wHeight)) return false;
    if (!(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)) return false;
    double currentTime = glfwGetTime();
    if (currentTime - coolDown < 1) return false;
    this->func();
    coolDown = currentTime;
    return true;
}

void Button2D::translate(float displacement, axis a) {
    if (a == X_AXIS) xpos += displacement;
    else if (a == Y_AXIS) ypos += displacement;
    if (buttonsShader) glUniform2fv(glGetUniformLocation(buttonsShader->getId(), "displacement"), 1, glm::value_ptr(glm::vec2(xpos * 2, -ypos * 2)));
}

void Button2D::move(float xpos, float ypos) {
    this->xpos = xpos;
    this->ypos = ypos;
    if (buttonsShader) glUniform2fv(glGetUniformLocation(buttonsShader->getId(), "displacement"), 1, glm::value_ptr(glm::vec2(xpos * 2, -ypos * 2)));
}

