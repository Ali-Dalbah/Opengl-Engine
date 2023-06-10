#include "../include/Window.h"

Window::Window(GLint width, GLint height, const std::string title):
    width(width),
    height(height), 
    title(title) {
    window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        throw std::__throw_bad_alloc;
    }
    glfwMakeContextCurrent(window);
	gladLoadGL();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        throw std::__throw_bad_alloc;
    }
}

void Window::setTitle(const std::string& title) {
    this->title = title;
    glfwSetWindowTitle(window, title.c_str());
}

bool Window::shouldClose() {return glfwWindowShouldClose(window);}

void Window::render() {
    scene->render();
}

void Window::setResizeCallBack(void(*function)(GLFWwindow*, GLint, GLint)) {
    glfwSetFramebufferSizeCallback(window, function);
}

void Window::setScrollCallBack(void(*function)(GLFWwindow*, double, double)) {
    glfwSetScrollCallback(window, function);
}

void Window::processInput(double delta) {
    if (customKeyFunc != NULL)
        customKeyFunc(window);
    if (scene!=NULL)
        scene->processInput(window, delta);
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::setScene(Scene& scene) {
    this->scene = &scene;
}

void Window::atLoopEnd() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::setKeyFunc(void(*customKeyFunc)(GLFWwindow*)) {
    this->customKeyFunc = customKeyFunc;
}

void Window::initGl() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
