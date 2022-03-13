#pragma once
#include "renderer.hpp"
#include <memory>

class GameObject
{
protected:
	glm::vec2 _position, _size;
	std::shared_ptr<Renderer> _renderer;
	GLuint _textureID;

public:
	GameObject();
	GameObject(std::string& textureID, std::shared_ptr<Renderer> renderer);
	GameObject(glm::vec2 size, std::string textureID, std::shared_ptr<Renderer> renderer);
	GameObject(glm::vec2 position, glm::vec2 size, std::string textureID, std::shared_ptr<Renderer> renderer);
	GameObject(std::shared_ptr<GameObject> gameObject);
	~GameObject() {};
	void draw();
	void loadTexture(std::string& path);
	void setPosition(glm::vec2 position);
	void setSize(glm::vec2 size);
	glm::vec2 getPos();
	glm::vec2 getSiz();
};
