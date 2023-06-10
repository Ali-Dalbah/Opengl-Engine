#ifndef EBO_H
#define EBO_H
#include "glad/glad.h"
#include <vector>
#include <glm/glm.hpp>
class EBO {
private:
    GLuint id;
public:
    EBO(std::vector <GLuint>&);
    GLuint getId();
    void bind();
    void unbind();
    ~EBO();
    void remove();
};
#endif 