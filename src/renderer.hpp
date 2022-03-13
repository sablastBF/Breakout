#pragma once
#include "shader.hpp"

#include <string>

class Renderer
{
private:
	/* data */
	unsigned int _bickVAO;
	unsigned int _VBO, _EBO;
	Shader _brickShader;
	glm::mat4 _model = glm::mat4(1.0f);
	glm::mat4 _projection = glm::mat4(1.0f);
	unsigned int _width = 0;
	unsigned int _height = 0;

public:
	Renderer(unsigned int width, unsigned int height, std::string pathVS, std::string pathFS);

	~Renderer() {};
	void initRender();
	void draw(glm::vec2, glm::vec2, unsigned int);

	void setShader(std::string, std::string);
	glm::mat4 getProjection();
	unsigned int getWidth();
	unsigned int getHeight();
};
