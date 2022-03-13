#pragma once
#include "shader.hpp"

#include "external/glad/glad.h"

#include "glm/glm.hpp"

#include <map>
#include <string>

class TextRenderer
{
private:
	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		glm::ivec2   Size;      // Size of glyph
		glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};
	Shader _shader;
	unsigned int _VAO, _VBO;
	std::map<GLchar, Character> _characters;

public:
	TextRenderer(std::string fontName, unsigned int width, unsigned int height);

	void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};
