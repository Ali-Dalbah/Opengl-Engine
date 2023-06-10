#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <string>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"
#include <vector>

enum axis {X_AXIS, Y_AXIS, Z_AXIS};

class Mesh {
public:
    std::vector <Vertex> vertices;
    std::vector <GLuint> indices;
    std::vector <Texture> textures;
    VAO vao;
    Mesh (std::vector <Vertex>&, std::vector <GLuint>&, std::vector <Texture>&);
    void render(Shader& , Camera&);
    void rotate(float , axis );
    void translate(float, axis);
    void setScale(float);
private:
    glm::mat4 matrix = glm::mat4(1.f);
    glm::vec3 translation = glm::vec3(0.f,0.f,0.f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::vec3 scale = glm::vec3(0.1f,0.1f,0.1f);
};
#endif