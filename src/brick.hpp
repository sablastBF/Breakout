#pragma once
#include "gameObject.hpp"

#include "irrklang/irrKlang.h"

#include <memory>
#include <string>

class Brick : public GameObject {
private:
	unsigned int _hitPoint = 0;
	unsigned int _breakScore = 1;
	unsigned int _addBalls = 0;
	bool _destroyed = false;
	bool _undestroyable = false;
	std::string _breakSound = "";
	std::string _hitSound = "";
	std::string _id = "";

public:
	Brick(std::shared_ptr<Brick>);
	Brick(std::string& textureID, std::shared_ptr<Renderer> renderer);
	unsigned int getBreakScore();
	unsigned int getHitPoint();
	unsigned int getNumberOfBalls();
	bool chekHit();
	bool getDestroyed();
	bool getUndestroyable();
	void draw();
	void playHitSound(irrklang::ISoundEngine* soundEngine);
	void playBreakSound(irrklang::ISoundEngine* soundEngine);
	void resetDestroid();
	void setBreakScore(unsigned int breakScore);
	void setBreakSound(std::string breakSound);
	void setDestroyed();
	void setHit(unsigned int hit);
	void setHitPoint(unsigned int hitPoint);
	void setHitSound(std::string hitSound);
	void setId(std::string id);
	void setNumberOfBalls(unsigned int numberOfBalls);
	void setUndestroyable(bool stateOfUnderstroyable);
	std::string getId();
};
