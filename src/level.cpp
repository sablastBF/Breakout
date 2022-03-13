#define _USE_MATH_DEFINES
#include "level.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void Level::draw() {
	_background->draw();
	_backgroundLevel->draw();
	_paddle->draw();
	for (std::shared_ptr<Brick> brick : _levelBrickLayout) {
		brick->draw();
	}

	for (std::shared_ptr<Ball> ball : _balls) {
		ball->draw();
	}
}

void Level::loadLevelFromFile(std::string path) {

	unsigned int n = 20, m = 20;
	unsigned int spacC = 0, rowC = 0;

	std::string pathBackground;
	tinyxml2::XMLDocument levelXml;
	levelXml.LoadFile(path.c_str());

	tinyxml2::XMLElement* levelData = levelXml.FirstChild()->ToElement();

	if (levelData->FindAttribute("NumberOfLives")) {
		levelData->FindAttribute("NumberOfLives")->QueryUnsignedValue(&_liveNumber);
	}
	else {
		_liveNumber = 3;
	}

	std::string paddleTexture;
	if (levelData->FindAttribute("PaddleTexture")) {
		paddleTexture = levelData->FindAttribute("PaddleTexture")->Value();
	}
	else {
		paddleTexture = "resources/textures/paddle/paddle.png";
		std::cout << "Background texture not found set to default." << std::endl;
	}

	glm::vec2 paddleSize = glm::vec2(_renderer->getWidth() * 0.17f, _renderer->getHeight() * 0.03f);
	_paddle = std::shared_ptr<Paddle>(new Paddle(paddleSize, paddleTexture, _renderer));


	std::string ballTexture;
	if (levelData->FindAttribute("BallTexture")) {
		ballTexture = levelData->FindAttribute("BallTexture")->Value();
	}
	else {
		ballTexture = "resources/textures/ball/ball.png";
		std::cout << "Background texture not found set to default." << std::endl;
	}

	_balls.push_back(std::shared_ptr<Ball>(new Ball(0.014f * _renderer->getWidth(), ballTexture, _renderer)));
	setBallPositionStuck();


	if (levelData->FindAttribute("LevelDifficulti")) {
		levelData->FindAttribute("LevelDifficulti")->QueryUnsignedValue(&_difficultyLevel);
	}
	else {
		_difficultyLevel = 1;
	}

	if (levelData->FindAttribute("RowCount")) {
		levelData->FindAttribute("RowCount")->QueryUnsignedValue(&m);
	}


	if (levelData->FindAttribute("ColumnCount")) {
		levelData->FindAttribute("ColumnCount")->QueryUnsignedValue(&n);
	}

	if (levelData->FindAttribute("RowSpacing")) {
		levelData->FindAttribute("RowSpacing")->QueryUnsignedValue(&rowC);
	}

	if (levelData->FindAttribute("ColumnSpacing")) {
		levelData->FindAttribute("ColumnSpacing")->QueryUnsignedValue(&spacC);
	}

	if (levelData->FindAttribute("BackgroundTexture")) {
		pathBackground = levelData->FindAttribute("BackgroundTexture")->Value();
	}
	else {
		pathBackground = "resources/textures/background/background.jpg";
	}

	std::string pathBackgroundLevel;
	if (levelData->FindAttribute("BackgroundTextureLevel")) {
		pathBackgroundLevel = levelData->FindAttribute("BackgroundTextureLevel")->Value();
	}

	float p = 0.25f;
	_background = std::shared_ptr<GameObject>(new GameObject(glm::vec2(0.0f), glm::vec2(_renderer->getWidth() * p, _renderer->getHeight()), pathBackground, _renderer));
	_backgroundLevel = std::shared_ptr<GameObject>(new GameObject(glm::vec2(_renderer->getWidth() * p, 0.0f), glm::vec2(_renderer->getWidth() * (1.0f - p), _renderer->getHeight()), pathBackgroundLevel, _renderer));

	tinyxml2::XMLElement* brickS = levelData->FirstChildElement("BrickTypes");
	brickS = brickS->FirstChildElement("BrickType");

	while (brickS != nullptr) {
		this->addBrick(brickS);
		brickS = brickS->NextSiblingElement("BrickType");
	}

	std::string levelOtline = levelData->FirstChildElement("Bricks")->GetText();
	std::vector<std::string> v;
	std::string levelID;

	for (int i = 0; i < levelOtline.length(); i++) {
		if (levelOtline[i] == '\t' || levelOtline[i] == '\n' || levelOtline[i] == ' ') {
			if (!levelID.empty())
				v.push_back(levelID);
			levelID.clear();
		}
		else {
			levelID.push_back(levelOtline[i]);
		}
	}
	if (!levelID.empty())
		v.push_back(levelID);


	float width_ = (1 - p) * static_cast<float>(_renderer->getWidth()) / (static_cast<float>(n));
	float height_ = 0.75f * static_cast<float>(_renderer->getHeight()) / (static_cast<float>(m));

	int k = 0;
	_offset = p * static_cast<float>(_renderer->getWidth());
	_balls[0]->setOffset(this->_offset);
	_paddle->setOffset(this->_offset);
	_paddle->restePosition();
	setBallPositionStuck();

	for (double i = 0; i < m; i++) {
		for (double j = 0; j < n; j++) {
			if (_brick.find(v[k]) == _brick.end()) {
				k++; continue;
			}
			std::shared_ptr<Brick> br = std::shared_ptr<Brick>(new Brick(_brick[v[k++]]));
			if (!br->getUndestroyable()) {
				_numberOfBricks++;
			}
			br->setPosition(glm::vec2(_offset + width_ * j, height_ * i));
			br->setSize(glm::vec2(width_ - rowC, height_ - spacC));
			_levelBrickLayout.push_back(br);
		}
	}

	_numberOfBricksOriginal = _numberOfBricks;
}

void Level::setBallPositionStuck() {
	glm::vec2 newPos = _paddle->getPos();
	newPos.x += _paddle->getSiz().x / 2.0f - _balls[0]->getRadius();
	newPos.y += -_balls[0]->getRadius() * 2.0f;
	_balls[0]->setPosition(newPos);
}

void Level::addBrick(tinyxml2::XMLElement* brick) {
	std::string id = brick->FindAttribute("Id")->Value();
	std::string texturePath = brick->FindAttribute("Texture")->Value();
	unsigned int hitPoints = 0;
	std::shared_ptr<Brick> brk = std::shared_ptr<Brick>(new Brick(texturePath, _renderer));
	if (brick->FindAttribute("HitPoints") == nullptr || std::string(brick->FindAttribute("HitPoints")->Value()) == std::string("Infinite")) {
		brk->setUndestroyable(true);
	}
	else {
		brick->FindAttribute("HitPoints")->QueryUnsignedValue(&hitPoints);
	}

	std::string soundPathBreak;
	if (brick->FindAttribute("BreakSound")) {
		soundPathBreak = brick->FindAttribute("BreakSound")->Value();
	}
	else {
		soundPathBreak = "resources/audio/bricks/Heart.wav";
	}

	std::string soundPathHit;
	if (brick->FindAttribute("HitSound")) {
		soundPathHit = brick->FindAttribute("HitSound")->Value();
	}
	else {
		soundPathHit = "resources/audio/bricks/Heart.wav";
		std::cout << "HitSound not specified, set to default path." << std::endl;
	}


	unsigned int breakScore;
	if (brick->FindAttribute("BreakScore")) {
		brick->FindAttribute("BreakScore")->QueryUnsignedValue(&breakScore);
	}
	else {
		breakScore = 0;
	}

	unsigned int numberOfBalls;
	if (brick->FindAttribute("AddBalls")) {
		brick->FindAttribute("AddBalls")->QueryUnsignedValue(&numberOfBalls);
	}
	else {
		numberOfBalls = 0;
	}
	brk->setHit(hitPoints);
	brk->setBreakScore(breakScore);
	brk->setBreakSound(soundPathBreak);
	brk->setHitSound(soundPathHit);
	brk->setNumberOfBalls(numberOfBalls);
	brk->setId(id);
	_brick[id] = brk;
}

Level::Level(std::string path, std::shared_ptr<Renderer> rendere) {
	_renderer = rendere;
	loadLevelFromFile(path);
}

std::vector<std::shared_ptr<Brick>>& Level::getBricks() {
	return _levelBrickLayout;
}

std::shared_ptr<Paddle> Level::getPaddle() {
	return _paddle;
}

std::shared_ptr<Ball> Level::getBall() {
	return _balls[0];
}

std::vector<std::shared_ptr<Ball> >& Level::getBalls() {
	return _balls;
}


void Level::addBalls(std::shared_ptr<Ball> ball, unsigned int numberOfBalls) {
	double normaX = 0.0, normaY = 0.0;
	double fi = 0.0;
	for (double i = 0; i < numberOfBalls; i++) {
		fi = i / numberOfBalls * 2.0 * M_PI;

		normaX = cos(fi);
		normaY = sin(fi);

		glm::vec2 newSpeed = glm::vec2(cos(fi), sin(fi));
		if (std::abs(newSpeed.x) < 0.02f) {
			if (newSpeed.x < 0.0f) {
				newSpeed.x = -0.0f;
			}else{
				newSpeed.x = 0.02f;
			}
		}
		if (std::abs(newSpeed.y) < 0.02f) {
			if (newSpeed.y < 0.0f) {
				newSpeed.y = -0.02f;
			} else {
				newSpeed.y = 0.02f;
			}
		}

		glm::vec2 newVelacity = (newSpeed * glm::length(ball->getVelocity()));
		std::shared_ptr<Ball> b = std::shared_ptr<Ball>(new Ball(ball, newVelacity));
		_balls.push_back(b);
	}
	_numberOfBalls += numberOfBalls;
}

void Level::decreseLive() {
	_liveNumber--;
}

unsigned int Level::getDifficultyLevel() {
	return _difficultyLevel;
}

unsigned int Level::getNumberOfBalls() {
	return _numberOfBalls;
}

unsigned int Level::getNumberOfBricks() {
	return _numberOfBricksOriginal;
}

unsigned int Level::getNumberOfLives() {
	return _liveNumber;
}

unsigned int Level::getNumberOfDistroid() {
	return _numberOfBricksOriginal - _numberOfBricks;
}

void Level::reste() {
	for (std::shared_ptr<Brick> brk : _levelBrickLayout) {
		if (brk->getDestroyed()) {
			brk->resetDestroid();
			brk->setHitPoint(_brick[brk->getId()]->getHitPoint());
		}
	}
	_numberOfBricks = _numberOfBricksOriginal;
	_balls.resize(1);
	_balls[0]->setStuck();
	_numberOfBalls = 1;
	_paddle->restePosition();
	setBallPositionStuck();
}

bool Level::isGameWon() {
	return _numberOfBricks <= 0;
}
void Level::destroyBrick() {
	_numberOfBricks--;
}
bool Level::doesGameHaveBall() {
	return _numberOfBalls <= 0;
}
void Level::destroyBall() {
	_numberOfBalls--;
}
