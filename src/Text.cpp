#include "../include/Text.h"
#include <ft2build.h>
#include FT_FREETYPE_H

Shader* Text::shader = NULL;
std::map<std::string, Text*> Text::fontsMap;

Text* Text::get(const char* fontName) {
    if (fontName == NULL) {
        std::map<std::string, Text*>::iterator it = Text::fontsMap.begin();
        if (it != Text::fontsMap.end()) return it->second;
        return NULL;
    }
    std::map<std::string, Text*>::iterator it = Text::fontsMap.find(fontName);
    if (it != Text::fontsMap.end()) return it->second;
    Text* font = new Text();
    font->load(fontName, 24);
    Text::fontsMap.insert(std::pair<std::string, Text*>(fontName, font));
    return fontsMap[fontName];
}

Text::Text() {
    if (Text::shader == NULL) Text::shader = new Shader("shaders/text.vert", "shaders/text.frag");
    glUniform1i(glGetUniformLocation(Text::shader->getId(), "text"), 0);
    // glm::mat4 proj = glm::ortho(0.f, (float)width, 0.f, (float)height);
    // glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::load(const char* font, unsigned int fontSize) {
    //std::cout<<"Loading font "<<font<<std::endl;
    charMap.clear();
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR Loading FreeType" << std::endl;
        FT_Done_FreeType(ft);
        return ;
    }
    FT_Face face;
    if (FT_New_Face(ft, font, 0, &face)) {
        std::cout << "ERROR Loading Font" << std::endl;
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return ;
    }
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char i = 0; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            std::cout << "ERROR failed to load Glyph" << std::endl;
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Char c = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
            };
        charMap.insert(std::pair<char, Char>(i, c));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Text::render(const char* string, float xpos, float ypos, float scale, glm::vec3 color) {
    glEnable(GL_BLEND);
    Text::shader->activate();
    glUniform3fv(glGetUniformLocation(Text::shader->getId(), "textColor"), 1, glm::value_ptr(color));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    while (*string != '\000') {
        Char c = charMap[*string];
        float x = xpos + c.bearing.x * scale;
        float y = ypos + (charMap['H'].bearing.y - c.bearing.y) * scale;
        float w = c.size.x * scale;
        float h = c.size.y * scale;
        float vertices[6][4] = {
            {y    , x + w, 0.0f, 1.0f},
            {y + h, x    , 1.0f, 0.0f},
            {y    , x    , 0.0f, 0.0f},
            {y    , x + w, 0.0f, 1.0f},
            {y + h, x + w, 1.0f, 1.0f},
            {y + h, x    , 1.0f, 0.0f},
        };
        glBindTexture(GL_TEXTURE_2D, c.glyphText);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        xpos += (c.offset >> 6) * scale;
        string++;
    }

    glDisable(GL_BLEND);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::remove(std::string& str) {
    std::map<std::string, Text*>::iterator it = Text::fontsMap.find(str);
    if (it != Text::fontsMap.end()) Text::fontsMap.erase(it);
}

Text::~Text() {

}