#pragma once
#include "gameObject.hpp"
#include <string>

class Ball : public GameObject {

private:
	bool _stuck = true;
	float _radius = 0.0f;
	float _offset = 0.0f;
	glm::vec2 _velocity = glm::vec2(0.0f, -400.0f);

public:
	Ball(float radius, std::string& text, std::shared_ptr<Renderer> r);
	Ball(std::shared_ptr<Ball> b, glm::vec2 velocity);

	bool getStuck();
	bool updatePos(float dt);
	float getRadius();
	void changeVelocity();
	void changeVelocityX();
	void changeVelocityY();
	void setOffset(float offset);
	void setStuck();
	void setUnStuck();
	void setVelocrty(glm::vec2 velocty);
	glm::vec2 getVelocity();
};