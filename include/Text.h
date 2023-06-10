#ifndef TEXT_H
#define TEXT_H
#include <map>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Shader.h"
#include "VAO.h"

struct Char{
    unsigned int glyphText;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int offset;
};

class Text{
    friend class std::map<char, Char>;
public:
    static Text* get(const char* = NULL);
    static void remove(std::string&);
    void render(const char*, float, float, float, glm::vec3 = glm::vec3(1.f, 1.f, 1.f));
private:
    Text();
    ~Text();
    void load(const char*, unsigned int);
    static std::map<std::string, Text*> fontsMap;
    static Shader* shader;
    float scale;
    glm::vec2 pos;
    std::map<char, Char> charMap;
    unsigned int vao;
    unsigned int vbo;
};

#endif