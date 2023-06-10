#ifndef CAMERA_H
#define CAMERA_H
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shader.h"
enum cameraType {FPS_CAMERA, STATIC_CAMERA, FREE_MOVING_CAMERA, ABSTRACT_CAMERA};
class Camera{
protected:
    Camera(glm::vec3, glm::vec3, float, float);
    void update();
    double lastX;
    double lastY;
    int width = 800;
    int height = 600;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float fov;
    bool click;
    ~Camera();
public:
    const static cameraType type = ABSTRACT_CAMERA;
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::mat4 projection;
    glm::vec3 right;
    glm::vec3 worldUp;
    void linkToShader(Shader&, const char*);
    virtual void processInput(GLFWwindow*, float);
    virtual void scroll(double);
    virtual void resize(int, int);
};

class FreeMovingCamera: public Camera {
public:
    const static cameraType type = FREE_MOVING_CAMERA;
    void processInput(GLFWwindow* , float) override;
    FreeMovingCamera(glm::vec3, glm::vec3, float, float);
    void scroll(double);
    void resize(int, int);
    ~FreeMovingCamera();
};

class StaticCamera: public Camera{
public:
    const static cameraType type = STATIC_CAMERA;
    void processInput(GLFWwindow* , float) override;
    StaticCamera(glm::vec3, glm::vec3, float, float);
    void scroll(double);
    void resize(int, int);
    ~StaticCamera();
};

class FPSCamera: public Camera{
public:
    const static cameraType type = FPS_CAMERA;
    void processInput(GLFWwindow* , float) override;
    FPSCamera(glm::vec3, glm::vec3, float, float);
    void scroll(double);
    void resize(int, int);
    ~FPSCamera();
};
#endif