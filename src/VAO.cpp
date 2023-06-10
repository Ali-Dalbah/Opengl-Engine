#include "../include/VAO.h"
VAO::VAO() {
    glGenVertexArrays(1, &id);
}

void VAO::linkVBOAttribute(VBO& vbo, GLuint layout,GLuint number,GLenum type,GLsizeiptr size, void* offset) {
    vbo.bind();
    glVertexAttribPointer(layout, number, type, GL_FALSE, size, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO::bind() {
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::remove() {
    glDeleteVertexArrays(1, &id);
}

GLuint VAO::getId() {return this->id;}

VAO::~VAO() {
}