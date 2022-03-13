#pragma once
#include "external/glad/glad.h"
#include "ball.hpp"
#include "brick.hpp"
#include "level.hpp"
#include "paddle.hpp"
#include "renderer.hpp"
#include "textRenderer.hpp"

#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "irrklang/irrKlang.h"

#include <memory>
#include <string>
#include <vector>

enum class GameState {
	RUNLEVEL,
	STARTSCREEN,
	ENDSCREEN,
	GAMEOVERSCREEN
};

class Game
{
private:
	GameState _gameState = GameState::STARTSCREEN;
	unsigned int _width, _height;
	std::shared_ptr<Level> _level = nullptr;
	std::shared_ptr<Renderer> _renderer = nullptr;
	unsigned int _numberOfLevels = 0;
	unsigned int _gameScore = 0;
	unsigned int _gameScoreCurrent = 0;
	std::vector<std::string> _levels;
	irrklang::ISoundEngine* _soundEngine = nullptr;
	GLFWwindow* _window = nullptr;
	std::shared_ptr<TextRenderer> _textRenderer;
	unsigned int _curetLevel = 0;
	float _deltaTime = 0.0f;
	bool _drawGameInfoFlag = false;

public:

	Game(unsigned int width, unsigned int height);
	~Game();

	static void framebuffer_size_callback(GLFWwindow* window, int width_, int height_);
	void procesInputForPaddle(GLFWwindow* window);

	GLFWwindow* createWindow(unsigned int width, unsigned int height);
	void draw();
	void updatePos(float deltaTime);
	bool checkCollision(std::shared_ptr<Ball> one, std::shared_ptr<GameObject> two);
	bool checkCollision(std::shared_ptr<GameObject> one, std::shared_ptr<GameObject> two);
	void addLevel(std::string path);
	void runGame();
	void runLevel(std::string path);

	void runStartScreen();
	void runEndScreen();
	void runGameOverScreen();
	GameState getGameState();
	std::shared_ptr<Level> getLevel();
	void setGameState(GameState v);
	void drawGameInfo();
	void setDrawGameInfoFlag(bool b = false);
	void setGameScoreCurrent(unsigned int t);
	void setGameScore(unsigned int t);
	void setCuretLevel(int curLvl);
};
