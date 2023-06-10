#include "../include/Camera.h"
Camera::Camera(glm::vec3 pos, glm::vec3 front, float width, float height):
    pos(pos),
    front(front),
    width(width),
    height(height) {
    this->lastX = 0;
    this->lastY = 0;
    up = glm::vec3(0.f,1.f,0.f);
    worldUp = up;
    yaw = 90.f;
    pitch = 0.f;
    speed = 10.0f;
    sensitivity = 0.1f;
    fov = 45.f;
    click = true;
}

void Camera::linkToShader(Shader& shader, const char* uniformName) {
    glUniformMatrix4fv(glGetUniformLocation(shader.getId(), uniformName), 1, GL_FALSE, glm::value_ptr(projection * glm::lookAt(pos, pos + front, up)));
}

void Camera::update() {
    glm::vec3 forward;
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(forward);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
    projection = glm::perspective(glm::radians(fov), (float)width / height, 0.1f, 1000.f);
}

void Camera::processInput(GLFWwindow* window, float delta) {}

void Camera::resize(int width, int height) {
    this->width = width;
    this->height = height;
}

void Camera::scroll(double offset) {
    fov -= (float)(offset);
    if (fov < -1.f) fov = -1.f;
    if (fov > 70.f) fov = 70.f;
}

StaticCamera::StaticCamera(glm::vec3 pos, glm::vec3 front, float width, float height): Camera(pos, front, width, height) {}

FPSCamera::FPSCamera(glm::vec3 pos, glm::vec3 front, float width, float height): Camera(pos, front, width, height) {}

FreeMovingCamera::FreeMovingCamera(glm::vec3 pos, glm::vec3 front, float width, float height): Camera(pos, front, width, height) {}

void FreeMovingCamera::processInput(GLFWwindow* window, float delta) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos += front * Camera::speed * delta;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos -= right * speed * delta;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos -= front * speed * delta;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos += right * speed * delta;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) pos += up * speed * delta;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) pos -= up * speed * delta;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        //std::cout<<"xpos "<<xpos/width<<" ypos "<<ypos/height<<std::endl;
        //glfwSetCursorPos(window, (float)(width/2), (float)(height/2));
        if (click) {
            click = false;
            lastX = xpos;
            lastY = ypos;
        }
        float xoffset, yoffset;
        xoffset = (float)(xpos - lastX) * sensitivity;
        yoffset = (float)(lastY - ypos) * sensitivity;
        yaw += xoffset;
        pitch += yoffset;
        if (pitch > 89.f) pitch = 89.f;
        if (pitch < -90.f) pitch = -89.f;
        lastX = xpos;
        lastY = ypos;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) click = true;
    update();
}

void StaticCamera::processInput(GLFWwindow* window, float delta) {}

void StaticCamera::resize(int w, int h) {
    Camera::resize(w, h);
}

void FreeMovingCamera::resize(int w, int h) {
    Camera::resize(w, h);
}

void FPSCamera::resize(int w, int h) {
    Camera::resize(w, h);
}

void StaticCamera::scroll(double x) {Camera::scroll(x);}

void FPSCamera::scroll(double x) {Camera::scroll(x);}

void FreeMovingCamera::scroll(double x) {Camera::scroll(x);}

void FPSCamera::processInput(GLFWwindow* window, float delta){}

Camera::~Camera() {
}

FPSCamera::~FPSCamera(){}

FreeMovingCamera::~FreeMovingCamera(){}

StaticCamera::~StaticCamera(){}