#include "../include/VBO.h"
VBO::VBO(std::vector <Vertex>& vertices) {
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO(float* vertices, int size) {
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() {glBindBuffer(GL_ARRAY_BUFFER, id);}
void VBO::unbind() {glBindBuffer(GL_ARRAY_BUFFER, 0);}

void VBO::remove() {
    glDeleteBuffers(1, &id);
}
VBO::~VBO() {}