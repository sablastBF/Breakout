#include "gameObject.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include <iostream>
void GameObject::draw() {
	_renderer->draw(_position, _size, _textureID);
}

GameObject::GameObject() {
}

GameObject::GameObject(std::string& texturePath, std::shared_ptr<Renderer> renderer) {
	loadTexture(texturePath);
	_renderer = renderer;
}

GameObject::GameObject(glm::vec2 siz, std::string texturePath, std::shared_ptr<Renderer> renderer) {
	_size = siz;
	loadTexture(texturePath);
	_renderer = renderer;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 siz, std::string texturePath, std::shared_ptr<Renderer> renderer) {
	_position = pos;
	_size = siz;
	loadTexture(texturePath);
	_renderer = renderer;
}

GameObject::GameObject(std::shared_ptr<GameObject> cop) {
	_textureID = cop->_textureID;
	_renderer = cop->_renderer;
}

void GameObject::setPosition(glm::vec2 pos) {
	_position = pos;
}

void GameObject::setSize(glm::vec2 siz) {
	_size = siz;
}

void GameObject::loadTexture(std::string& path) {
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width, height, nrChannels;
	unsigned char* data = nullptr;

	if (path.substr(path.find_last_of(".") + 1) == "png") {
		data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
	}
	else {
		data = stbi_load(path.c_str(), &width, &height, &nrChannels, 3);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	std::cout << path << std::endl;
	if (data) {
		if (path.substr(path.find_last_of(".") + 1) == "png") {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

glm::vec2 GameObject::getPos() {
	return _position;
}

glm::vec2 GameObject::getSiz() {
	return _size;
}
