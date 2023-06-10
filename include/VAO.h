#ifndef VAO_H
#define VAO_H
#include "glad/glad.h"
#include <glm/glm.hpp>
#include "VBO.h"
class VAO {
private:
    GLuint id;
public:
    VAO();
    GLuint getId(void);
    void linkVBOAttribute(VBO&,GLuint,GLuint,GLenum,GLsizeiptr,void*);
    void bind();
    void unbind();
    ~VAO();
    void remove();
};
#endif 