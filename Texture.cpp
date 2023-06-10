#include "../include/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb/stb_image.h"
Texture::Texture(const char* imageFile, const char* type, GLuint texNum) {
    Texture::type = type;
    //std::cout<<imageFile<<std::endl;
    int width, height, numberOfColors;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* img = stbi_load(imageFile, &width, &height, &numberOfColors, 0);
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + texNum);
    Texture::texNum = texNum;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST /*GL_LINEAR*/);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if (numberOfColors == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    else if (numberOfColors == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    else if (numberOfColors == 1) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, img);
    else throw std::invalid_argument("Failed Loading Texture");
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(img);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::linkToShader(Shader& shader, const char* uniformName, GLuint unit) {
    GLuint uniform = glGetUniformLocation(shader.getId(), uniformName);
    shader.activate();
    glUniform1i(uniform, unit);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + texNum);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::remove() {
    glDeleteTextures(1, &id);
}

Texture::~Texture() {}