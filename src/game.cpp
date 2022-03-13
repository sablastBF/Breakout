#include "game.hpp"

extern Game* brakeOut; /* Declaration of the variable */

void procesInput(GLFWwindow* window, int key, int scancode, int action, int mods);

Game::Game(unsigned int width, unsigned int height) {
	_width = width;
	_height = height;
}

Game::~Game() {
	_soundEngine->drop();
}

void Game::addLevel(std::string pathToLevel) {
	_levels.push_back(pathToLevel);
	_numberOfLevels++;
}

GameState Game::getGameState() {
	return _gameState;
}
inline std::shared_ptr<Level> Game::getLevel() {
	return _level;
}
void Game::setGameState(GameState v) {
	_gameState = v;
}

void Game::runGame() {
	_window = createWindow(_width, _height);
	_soundEngine = irrklang::createIrrKlangDevice();
	_textRenderer = std::shared_ptr<TextRenderer>(new TextRenderer("resources/fonts/AmaticSC-Regular.ttf", _width, _height));

	if (!_window) return;
	_renderer = std::shared_ptr<Renderer>(new Renderer(_width, _height, "resources/shaders/basic_brick.vs", "resources/shaders/basic_brick.fs"));

	_curetLevel = 0;
	glfwSetKeyCallback(_window, procesInput);


	while (!glfwWindowShouldClose(_window)) {
		if (_gameState == GameState::STARTSCREEN) {
			runStartScreen();
		}

		if (_gameState == GameState::RUNLEVEL) {
			runLevel(_levels[_curetLevel++]);

			if (_gameState == GameState::RUNLEVEL && _curetLevel == _numberOfLevels) {
				_gameState = GameState::ENDSCREEN;
			}
		}

		if (_gameState == GameState::GAMEOVERSCREEN) {
			runGameOverScreen();
		}

		if (_gameState == GameState::ENDSCREEN) {
			runEndScreen();
		}
	}

}

void Game::runLevel(std::string levelPath) {
	_level = std::shared_ptr<Level>(new Level(levelPath, _renderer));

	float lastFrame = 0.0f;
	float currentFrame = 0.0f;
	_soundEngine->play2D("resources/audio/background/light_buzzing.mp3", true);

	std::string sc;
	std::string numberOfBalls, numberOfBrick, lives;
	std::string levelNumber, numberOfDistroid;

	_drawGameInfoFlag = 1;

	while (_gameState == GameState::RUNLEVEL && !glfwWindowShouldClose(_window)) {
		currentFrame = glfwGetTime();
		_deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		procesInputForPaddle(_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		updatePos(_deltaTime);
		draw();
		if (_level->isGameWon()) {
			_gameScore += _gameScoreCurrent;
			_gameScoreCurrent = 0;
			_gameScore += (_level->getDifficultyLevel() * 1000.0f - currentFrame) + (_level->getNumberOfBalls() - 1) * 100 + _level->getNumberOfLives() * 1500;
			_level->setBallPositionStuck();
			return;
		}
		if (_level->doesGameHaveBall()) {
			_gameScoreCurrent = 0;
			_level->reste();
			_level->decreseLive();
			if (_level->getNumberOfLives() == 0) _gameState = GameState::GAMEOVERSCREEN;
		}

		sc = std::to_string(_gameScore + _gameScoreCurrent);
		numberOfBalls = std::to_string(_level->getNumberOfBalls());
		numberOfBrick = std::to_string(_level->getNumberOfBricks());
		numberOfDistroid = std::to_string(_level->getNumberOfDistroid());
		levelNumber = std::to_string(_curetLevel);
		lives = std::to_string(_level->getNumberOfLives());
		float k = 0.0f;
		float of = 5.0f;
		_textRenderer->RenderText("Score: " + sc, 5.0f, of + 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("Level: " + levelNumber, 5.0f, of + 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("Balls: " + numberOfBalls, 5.0f, of + 60.0f * (k++), 1.0f, glm::vec3(1.0f));

		_textRenderer->RenderText(numberOfDistroid + " / " + numberOfBrick, 5.0f, of + 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("Brick: ", 5.0f, of + 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("Lives: " + lives, 5.0f, _renderer->getHeight() - 60.0f, 1.0f, glm::vec3(1.0f));

		if (_drawGameInfoFlag) {
			drawGameInfo();
		}

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	_soundEngine->stopAllSounds();
}

void Game::drawGameInfo() {
	int k = 3;
	_textRenderer->RenderText("Press Space to play", _renderer->getWidth() / 2.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
	_textRenderer->RenderText("LEFT & RIGHT ARROW TO MOVE ", _renderer->getWidth() / 2.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
	_textRenderer->RenderText("R TO RESET ", _renderer->getWidth() / 2.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
	_textRenderer->RenderText("ESC TO QUIT ", _renderer->getWidth() / 2.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
}

inline void Game::setDrawGameInfoFlag(bool drawGameInfoFlag) {
	_drawGameInfoFlag = drawGameInfoFlag;
}

inline void Game::setGameScoreCurrent(unsigned int gameScoreCurrent) {
	_gameScoreCurrent = gameScoreCurrent;
}

inline void Game::setGameScore(unsigned int gameScore) {
	_gameScore = gameScore;
}

inline void Game::setCuretLevel(int curetLevel) {
	_curetLevel = curetLevel;
}

void Game::draw() {
	_level->draw();
}

GLFWwindow* Game::createWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return nullptr;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return window;
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//STARTSCREEN
void Game::runStartScreen() {
	_soundEngine->play2D("resources/audio/background/UA.mp3", true);

	while (_gameState == GameState::STARTSCREEN && !glfwWindowShouldClose(_window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		int k = 1;
		_textRenderer->RenderText("BRAKEOUT BY BARBA", 5.0f, 60.0f, 1.5f, glm::vec3(1.0f));
		_textRenderer->RenderText("Press SPACE to play", 5.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("ESC TO QUIT ", 5.0f, _renderer->getHeight() - 60.0f * (k++), 0.5f, glm::vec3(1.0f));
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	_soundEngine->stopAllSounds();
}

void Game::runEndScreen() {
	_soundEngine->play2D("resources/audio/background/UA.mp3", true);

	while (_gameState == GameState::ENDSCREEN && !glfwWindowShouldClose(_window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		int k = 1;
		_textRenderer->RenderText("WICTORY", 5.0f, 60.0f, 1.5f, glm::vec3(1.0f));
		_textRenderer->RenderText("Your Sroe is: " + std::to_string(_gameScore), 5.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("Press R to rest game", 5.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("ESC TO QUIT ", 5.0f, _renderer->getHeight() - 60.0f * (k++), 0.5f, glm::vec3(1.0f));
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	_soundEngine->stopAllSounds();
}

void Game::runGameOverScreen() {
	_soundEngine->play2D("resources/audio/background/buzzing.mp3", true);

	while (_gameState == GameState::GAMEOVERSCREEN && !glfwWindowShouldClose(_window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		int k = 1;
		_textRenderer->RenderText("Game OVER", 5.0f, 60.0f, 1.5f, glm::vec3(1.0f));
		_textRenderer->RenderText("Your Score is: " + std::to_string(_gameScore), 5.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("Press R to reset game", 5.0f, _renderer->getHeight() - 60.0f * (k++), 1.0f, glm::vec3(1.0f));
		_textRenderer->RenderText("ESC TO QUIT ", 5.0f, _renderer->getHeight() - 60.0f * (k++), 0.5f, glm::vec3(1.0f));

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	_soundEngine->stopAllSounds();
}

bool Game::checkCollision(std::shared_ptr<GameObject> one, std::shared_ptr<GameObject> two) // AABB - AABB collision
{
	bool collisionX = one->getPos().x + one->getSiz().x > two->getPos().x &&
		two->getPos().x + two->getSiz().x > one->getPos().x;

	bool collisionY = one->getPos().y + one->getSiz().y > two->getPos().y &&
		two->getPos().y + two->getSiz().y > one->getPos().y;
	return collisionX && collisionY;
}


void Game::updatePos(float dt) {
	std::shared_ptr<Paddle> paddle = _level->getPaddle();
	std::vector<std::shared_ptr<Brick>>& bricks = _level->getBricks();
	std::vector<std::shared_ptr<Ball>>& balls = _level->getBalls();
	int siz = balls.size();
	std::shared_ptr<Ball> b = nullptr;
	for (int i = 0; i < siz; i++) {
		b = balls[i];
		if (b->updatePos(dt)) {
			_level->destroyBall();
			if (!_level->doesGameHaveBall())
				balls.erase(balls.begin() + i);
			i--; siz--;
			continue;
		}

		if (checkCollision(b, paddle)) {
			// uzmemo pozicju lopte, pozicju paddla 
			//ball -> changeVelocityY();

			glm::vec2 bp = b->getPos() + b->getRadius();
			glm::vec2 pad = paddle->getPos() + paddle->getSiz() / 2.0f;
			glm::vec2 newVelocty = bp - pad;
			newVelocty.y -= paddle->getSiz().x * 2.0f;
			newVelocty.y /= 5.0;
			newVelocty = normalize(newVelocty);
			b->setVelocrty(newVelocty * glm::length(b->getVelocity()));
		}

		// izmedu lopte i brikova

		for (int i = bricks.size() - 1; ~i; i--) {
			if (bricks[i]->getDestroyed()) {
				continue;
			}

			if (checkCollision(b, bricks[i])) {
				if (bricks[i]->getUndestroyable() == false && bricks[i]->chekHit()) {
					_gameScoreCurrent += bricks[i]->getBreakScore();
					bricks[i]->setDestroyed();
					_level->destroyBrick();
					bricks[i]->playBreakSound(_soundEngine);
					_level->addBalls(b, bricks[i]->getNumberOfBalls());
				}
				else {
					bricks[i]->playHitSound(_soundEngine);
				}
				break;
			}
		}
	}
}

// ovo tude treba ispraviti 
bool Game::checkCollision(std::shared_ptr<Ball> ball, std::shared_ptr<GameObject> two) {

	glm::vec2 center(ball->getPos() + ball->getRadius());
	glm::vec2 aabb_half_extents(two->getSiz().x / 2.0f, two->getSiz().y / 2.0f);
	glm::vec2 aabb_center(
		two->getPos().x + aabb_half_extents.x,
		two->getPos().y + aabb_half_extents.y);

	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	if (glm::length(difference) > ball->getRadius()) return false;


	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++) {
		float dot_product = glm::dot(glm::normalize(difference), compass[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}

	if (best_match == 1 || best_match == 3) {
		ball->changeVelocityX(); // reverse horizontal velocity
		// relocate
		float penetration = ball->getRadius() - std::abs(difference.x);
		glm::vec2 pos = ball->getPos();
		if (best_match == 3) {
			pos.x += penetration;
		}
		else {
			pos.x -= penetration;
		}
		ball->setPosition(pos);
	}
	else {
		ball->changeVelocityY(); // reverse horizontal velocity
		// relocate
		float penetration = ball->getRadius() - std::abs(difference.y);
		glm::vec2 pos = ball->getPos();
		if (best_match == 2) {
			pos.y += penetration;
		}
		else {
			pos.y -= penetration;
		}
		ball->setPosition(pos);
	}

	return true;
}

void Game::procesInputForPaddle(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (_gameState == GameState::RUNLEVEL) {
		std::shared_ptr<Paddle> paddle = _level->getPaddle();
		std::shared_ptr<Ball> ball = _level->getBall(); int state = glfwGetKey(window, GLFW_KEY_E);

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			paddle->updatePos(glm::vec2(-1.0f, 0.0f), _deltaTime);
			if (ball->getStuck()) {
				_level->setBallPositionStuck();
			}
			_drawGameInfoFlag = 0;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			paddle->updatePos(glm::vec2(1.0f, 0.0f), _deltaTime);
			if (ball->getStuck()) {
				_level->setBallPositionStuck();
			}
			_drawGameInfoFlag = 0;
		}
	}
}

void procesInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	switch (brakeOut->getGameState()) {
	case GameState::STARTSCREEN:
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			brakeOut->setGameState(GameState::RUNLEVEL);
			brakeOut->setDrawGameInfoFlag(0);
		}
		break;

	case GameState::RUNLEVEL:
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			brakeOut->getLevel()->getBall()->setUnStuck();
			brakeOut->setDrawGameInfoFlag(0);
		}
		// reset
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			brakeOut->setGameScoreCurrent(0);
			brakeOut->getLevel()->reste();
		}
		break;

	case GameState::ENDSCREEN:
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			brakeOut->setGameState(GameState::STARTSCREEN);
			brakeOut->setCuretLevel(0);
			brakeOut->setGameScoreCurrent(0);
			brakeOut->setGameScore(0);

		}
		break;

	case GameState::GAMEOVERSCREEN:
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			brakeOut->setGameState(GameState::STARTSCREEN);
			brakeOut->setCuretLevel(0);
			brakeOut->setGameScoreCurrent(0);
			brakeOut->setGameScore(0);
		}
		break;
	}
}

