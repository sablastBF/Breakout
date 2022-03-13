#include "ball.hpp"
#include "glm/gtc/matrix_transform.hpp"

Ball::Ball(float radius, std::string& text, std::shared_ptr<Renderer> r) : GameObject(glm::vec2(2.0f * radius), text, r) {
	_radius = radius;
}

// dodavanje novih lopta, namjenjeno je za vise lopta
Ball::Ball(std::shared_ptr<Ball> b, glm::vec2 velocity) {
	_radius = b->_radius;
	_renderer = b->_renderer;
	_position = b->_position;
	_size = b->_size;
	_velocity = velocity;
	_textureID = b->_textureID;
	_stuck = false;
	_offset = b->_offset;
}

bool Ball::updatePos(float dt) {
	if (_stuck) {
		return false;
	}

	glm::vec2 newPos = _position + _velocity * dt;
	if (newPos.x < _offset || newPos.x + _radius * 2.0f > _renderer->getWidth()) {
		_velocity.x = -_velocity.x;
	}

	if (newPos.y < 0.0f) {
		_velocity.y = -_velocity.y;
	}
	if (newPos.y + _radius * 2.0f > _renderer->getHeight()) {
		return true;
	}

	newPos = glm::clamp(newPos, glm::vec2(_offset, 0.0f), glm::vec2(_renderer->getWidth() - 2.0f * _radius, _renderer->getHeight() - 2.0f * _radius));

	_position = newPos;
	return false;
}
void Ball::setOffset(float offset) {
	_offset = offset;
}

float Ball::getRadius() {
	return _radius;
}

void Ball::changeVelocity() {
	_velocity.x = -_velocity.x;
	_velocity.y = -_velocity.y;
}

void Ball::changeVelocityY() {
	_velocity.y = -_velocity.y;
}
void Ball::changeVelocityX() {
	_velocity.x = -_velocity.x;
}

glm::vec2 Ball::getVelocity() {
	return _velocity;
}

void Ball::setVelocrty(glm::vec2 velocity) {
	_velocity = velocity;
}

void Ball::setUnStuck() {
	_stuck = false;
}
void Ball::setStuck() {
	_stuck = true;
}

bool Ball::getStuck() {
	return _stuck;
}

