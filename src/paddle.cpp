#include "paddle.hpp"

#include <iostream>

Paddle::Paddle(glm::vec2 siz, std::string texture, std::shared_ptr<Renderer> r)
	:GameObject(glm::vec2(0.0f), siz, texture, r) {
}

void Paddle::updatePos(glm::vec2 direction, float dt) {
	glm::vec2 newPos = this->_position + direction * _velocity * dt;
	this->_position = glm::clamp(newPos, glm::vec2(this->_offset, 0.0f), glm::vec2(_renderer->getWidth() - _size.x, _renderer->getHeight()));
}

void Paddle::updateVelocty(glm::vec2 velocity) {
	_velocity = velocity;
}

void Paddle::restePosition() {
	_position.x = (_renderer->getWidth() + this->_offset) / 2.0f - _size.x / 2.0f;
	_position.y = _renderer->getHeight() - _size.y;
}

void Paddle::setOffset(float offset) {
	_offset = offset;
}
