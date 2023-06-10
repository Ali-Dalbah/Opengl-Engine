#include "include/Model.h"
#include "include/SkyBox.h"
#include "include/glad/glad.h"
#include "include/Button2D.h"
#include "include/Window.h"
#include <cstdlib>
#include <unistd.h>
#include "include/Text.h"
#include "include/SoundBuffer.h"
#include "include/SoundObject.h"
#include "include/SoundDevice.h"
#define FPS 60
FreeMovingCamera camera(glm::vec3(0.f,1.f,-5.f), glm::vec3(0.f,1.f,0.f), 800, 600);
StaticCamera staticCamera(glm::vec3(0.f,1.f,-5.f), glm::vec3(0.f,1.f,0.f), 800, 600);
Scene startScene(&staticCamera);
Scene scene(&camera);
void mouseScrollCallback(GLFWwindow*, double, double);
void resize(GLFWwindow*,GLint,GLint);

int main(int argc, char** argv) {
    Window::initGl();
    static Window window(800, 600, "title");
    Shader skyShader("shaders/skybox.vert","shaders/skybox.frag");
    Shader buttonsShader("shaders/button.vert", "shaders/button.frag");
    Shader shader("shaders/shader.vert", "shaders/shader.frag");
    Text* t = Text::get("fonts/BitterPro-Black.ttf");
	glEnable(GL_DEPTH_TEST);
    // glEnable(GL_STENCIL_TEST);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    glDepthFunc(GL_LESS);
    //Shader st("shaders/hitbox.vert", "shaders/hitbox.frag");
	Component component("resources/dust2/src/de_dust2.obj");
    component.setShader(shader);
    startScene.setButtonsShader(buttonsShader);
    scene.addComponent(component);
    window.setScene(startScene);
    window.setKeyFunc([] (GLFWwindow* win) {
        if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            window.setScene(startScene);
    });
    Button2D but(0.1f,0.1f,0.0f,0.0f, []() {
        window.setScene(scene);
    });
    startScene.addButton(but);
    but.translate(0.25f, X_AXIS);
    but.translate(0.2f, Y_AXIS);
    component.rotate(-90.f,X_AXIS);
    unsigned int fpsCounter = 0;
	double prev = glfwGetTime();
	double current = glfwGetTime();
	window.setScrollCallBack(mouseScrollCallback);
    window.setResizeCallBack(resize);
    SkyBox sky(800, 600, &skyShader);
    scene.setSkyBox(sky);
    SoundDevice* sndDvc = SoundDevice::get();
    SoundBuffer* sndBuff = SoundBuffer::get();
    unsigned int music = sndBuff->addSound("resources/music.wav");
    SoundObject sndObj;
    sndObj.play(music);
    sndObj.setGain(0.03f);
    while(!window.shouldClose()) {
		current = glfwGetTime();
        fpsCounter++;
        if (current - prev >= 1.0/FPS) {
            std::string str = std::to_string(1.0/(current-prev)*fpsCounter);
            window.processInput(current - prev);
            window.setTitle(str.c_str());
            fpsCounter = 0;
		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT/* | GL_STENCIL_BUFFER_BIT*/);
            t->render("hello aapgj$aa", 0.f, 0.f, .002f);
            // glStencilMask(0xFF);
            // model.render(shader, camera);
            // but.render(camera);
            // but.onClick(window, 800, 600);
            // sky.render(camera);
            // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            // glStencilMask(0x00);
            // glDisable(GL_DEPTH_TEST);
            // st.activate();
            // glUniform1f(glGetUniformLocation(st.getId(), "outlining"), 0.08f);
            // model.render(st, camera);
            // glStencilMask(0xFF);
            // glStencilFunc(GL_ALWAYS, 0, 0xFF);
            // glEnable(GL_DEPTH_TEST);
            window.render();
            prev = current;
            window.atLoopEnd();
        }
    }
    window.~Window();
    glfwTerminate();
	return 0;
}

void resize(GLFWwindow *window, GLint width, GLint height) {
    glViewport(0, 0, width, height);
    camera.resize(width, height);
}

void mouseScrollCallback(GLFWwindow*, double x, double y) {
	camera.scroll(y);
}