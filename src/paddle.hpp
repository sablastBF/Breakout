#pragma once
#include "gameObject.hpp"

#include <memory>
#include <string>

class Paddle : public GameObject
{
private:
	glm::vec2 _velocity = glm::vec2(500.0f);
	float _offset = 0.0f;

public:
	Paddle(glm::vec2 size, std::string texture, std::shared_ptr<Renderer>);
	~Paddle() {};

	void updatePos(glm::vec2, float time);
	void updateVelocty(glm::vec2 velocity);
	void restePosition();
	void setOffset(float _offset);
};
