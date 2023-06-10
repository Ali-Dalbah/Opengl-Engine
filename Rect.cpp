#include "../include/Rect.h"

Rect::Rect (float width, float height): vao() {
    float triangle_vertices[] = {
        -width - 1.f, -height + 1.f,
        -width - 1.f,  height + 1.f,
         width - 1.f, -height + 1.f,
         width - 1.f,  height + 1.f
    };
    std::vector<unsigned int> vec({0 , 1, 2, 3 , 2, 1});
    vao.bind();
    VBO vbo(triangle_vertices, 12);
    EBO ebo(vec);
    vao.linkVBOAttribute(vbo, 0, 2, GL_FLOAT, 0, (void *) 0);
    vao.unbind();
    ebo.unbind();
}

void Rect::render() {
    vao.bind();
    glDrawElements(GL_TRIANGLES, sizeof(unsigned int) * 4, GL_UNSIGNED_INT, 0);
    vao.unbind();
}