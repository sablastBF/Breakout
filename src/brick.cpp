#include "Brick.hpp"

void Brick::draw() {
	if (_destroyed) {
		return;
	}
	GameObject::draw();
}

void Brick::setDestroyed() {
	_destroyed = true;
}
void Brick::resetDestroid() {
	_destroyed = false;
}

bool Brick::getDestroyed() {
	return _destroyed;
}

bool Brick::getUndestroyable() {
	return _undestroyable;
}

void Brick::setUndestroyable(bool stateOfUnderstroyable) {
	_undestroyable = stateOfUnderstroyable;
}

void Brick::setNumberOfBalls(unsigned int addBalls) {
	_addBalls = addBalls;
}

unsigned int Brick::getNumberOfBalls() {
	return _addBalls;
}

unsigned int Brick::getBreakScore() {
	return _breakScore;
}

bool Brick::chekHit() {
	_hitPoint--;
	return _hitPoint <= 0;
}

void Brick::setHit(unsigned int hit) {
	_hitPoint = hit;
}

void Brick::setBreakScore(unsigned int breakScore) {
	_breakScore = breakScore;
}

void Brick::setBreakSound(std::string breakSound) {
	_breakSound = breakSound;
}

void Brick::setId(std::string id) {
	_id = id;
}

Brick::Brick(std::shared_ptr<Brick> b) {
	_textureID = b->_textureID;
	_hitPoint = b->_hitPoint;
	_breakScore = b->_breakScore;
	_undestroyable = b->_undestroyable;
	_renderer = b->_renderer;
	_breakSound = b->_breakSound;
	_hitSound = b->_hitSound;
	_addBalls = b->_addBalls;
	_id = b->_id;
}

Brick::Brick(std::string& textureID, std::shared_ptr<Renderer> renderer) : GameObject(textureID, renderer) {
}

void Brick::setHitSound(std::string hitSound) {
	_hitSound = hitSound;
}

void Brick::playHitSound(irrklang::ISoundEngine* soundEngine) {
	soundEngine->play2D(_hitSound.c_str(), false);
}

void Brick::playBreakSound(irrklang::ISoundEngine* soundEngine) {
	soundEngine->play2D(_breakSound.c_str(), false);
}

unsigned int Brick::getHitPoint() {
	return _hitPoint;
}
void Brick::setHitPoint(unsigned int point) {
	_hitPoint = point;
}

std::string Brick::getId() {
	return _id;
}
