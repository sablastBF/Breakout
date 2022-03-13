#pragma once
#include "ball.hpp"
#include "brick.hpp"
#include "gameObject.hpp"
#include "paddle.hpp"

#include "external/tinyxml2/tinyxml2.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

class Level {
private:
	std::map<std::string, std::shared_ptr<Brick>> _brick;
	std::shared_ptr<Renderer> _renderer = nullptr;
	std::vector<std::shared_ptr<Brick>> _levelBrickLayout;

	std::shared_ptr<GameObject> _background = nullptr;
	std::shared_ptr<GameObject> _backgroundLevel = nullptr;

	std::shared_ptr<Paddle> _paddle = nullptr;
	std::vector<std::shared_ptr<Ball>> _balls;
	unsigned int _numberOfBalls = 1;
	unsigned int _numberOfBricks = 0;
	unsigned int _numberOfBricksOriginal = 0;
	unsigned int _difficultyLevel = 1;
	unsigned int _liveNumber = 0;
	float _offset = 0.0f;

public:
	Level(std::string path, std::shared_ptr<Renderer> renderer);

	~Level() {
	};
	void draw();
	void loadLevelFromFile(std::string path);
	void addBrick(tinyxml2::XMLElement* element);
	std::vector<std::shared_ptr<Brick>>& getBricks();

	std::shared_ptr<Paddle> getPaddle();
	std::shared_ptr<Ball> getBall();
	void setBallPositionStuck();
	void addBalls(std::shared_ptr<Ball> ball, unsigned int numberOfBalls);
	std::vector<std::shared_ptr<Ball> >& getBalls();

	void reste();
	bool isGameWon();
	void destroyBrick();
	void destroyBall();
	bool doesGameHaveBall();
	void decreseLive();

	unsigned int getDifficultyLevel();
	unsigned int getNumberOfBalls();
	unsigned int getNumberOfBricks();
	unsigned int getNumberOfLives();
	unsigned int getNumberOfDistroid();
};

