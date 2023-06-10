#ifndef VBO_H
#define VBO_H
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>
struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texture;
};
class VBO {
private:
    GLuint id;
public:
    VBO(std::vector<Vertex>&);
    VBO(float*, int);
    GLuint getId(void);
    void bind();
    void unbind();
    ~VBO();
    void remove();
};
#endif