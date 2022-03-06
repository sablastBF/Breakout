#pragma once
#include "shader.hpp"
#include <map>

using namespace std;
class textRender
{
private:
    struct Character {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2   Size;      // Size of glyph
        glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };

    Shader shader;
    unsigned int VAO, VBO;
    map<GLchar, Character> Characters;

public:
    textRender(string fontName, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);

    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

    ~textRender(){}

    
};



