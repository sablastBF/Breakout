#pragma once

#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <irrklang/irrKlang.h>
#include <memory>

#include "glm/gtc/matrix_transform.hpp"
#include "level.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "Rendere.hpp"
#include "textRender.hpp"


enum GameState{
    RUNLEVEL,
    STARTSCREEN,
    ENDSCREEN,
    GAMEOVERSCREEN
};

class Game
{
   
private:
    GameState gameState = STARTSCREEN;
   // glm::mat4 projection;
    unsigned int width, height;
    shared_ptr<Level> level = nullptr;
    shared_ptr<Renderer> render = nullptr;
    shared_ptr<Renderer> brickRender = nullptr;
    unsigned int numberOfLevels = 0;
    unsigned int gameScore = 0;
    vector<string> levels;
    ISoundEngine* SoundEngine = nullptr;
    GLFWwindow* window;
    shared_ptr<textRender> TextRender;
    unsigned int curetLevel = 0;
    float deltaTime;
public:

    Game(unsigned int width_, unsigned int height_);
    ~Game(){SoundEngine -> drop();}

    static void framebuffer_size_callback(GLFWwindow* window, int width_, int height_);
    GLFWwindow*  crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void draw();
    void updatePos(float dt);
    bool CheckCollision(shared_ptr<Ball> one, shared_ptr<GameObject> two);
    bool CheckCollision(shared_ptr<GameObject> one, shared_ptr<GameObject> two); 
    void addLevel(string path);
    void RunGame();
    void RunLevel(string path);

    void RunStartScreen();
    void RunEndScreen();
    void RunGameOverScreen();
    GameState getGameState();
    shared_ptr<Level> getLevel(){return this -> level;}
    void setGameState(GameState v);
    float  getDeltaTime(){return this -> deltaTime;}

};

