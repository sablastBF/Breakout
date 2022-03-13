#include "renderer.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void Renderer::draw(glm::vec2 pos, glm::vec2 siz, unsigned int textureID) {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	_brickShader.use();
	_brickShader.setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f)), glm::vec3(siz, 0.0f)));
	_brickShader.setMat4("projection", _projection);

	glBindVertexArray(_bickVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::initRender() {
	float vertices[] = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};


	unsigned int indices[] = {
		0, 1, 3,
		0, 2, 3
	};

	glGenVertexArrays(1, &_bickVAO);

	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);
	glBindVertexArray(_bickVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::setShader(std::string vertexPath, std::string fragmetPath) {
	_brickShader = Shader(vertexPath.c_str(), fragmetPath.c_str());
	_brickShader.use();
}

 glm::mat4 Renderer::getProjection() {
	return _projection;
}

Renderer::Renderer(unsigned int width, unsigned int height, std::string pathVS, std::string pathFS) {
	_width = width;
	_height = height;

	initRender();
	this->setShader(pathVS, pathFS);
	this->_projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
}

unsigned int Renderer::getHeight() {
	return this->_height;
}

unsigned int Renderer::getWidth() {
	return this->_width;
}
