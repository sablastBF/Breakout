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

class Game
{
private:
    glm::mat4 projection;
    unsigned int width, height;
    shared_ptr<Level> level = nullptr;
    shared_ptr<Renderer> render = nullptr;
    shared_ptr<Renderer> brickRender = nullptr;
    unsigned int numberOfLevels = 0;
    unsigned int gameScore = 0;
    vector<string> levels;
    ISoundEngine* SoundEngine = nullptr;
    GLFWwindow* window;
    
public:

    Game(unsigned int width_, unsigned int height_);
    ~Game(){SoundEngine -> drop();}

    static void framebuffer_size_callback(GLFWwindow* window, int width_, int height_);
    void processInput(GLFWwindow *window, float dt);
    GLFWwindow*  crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void draw();
    void updatePos(float dt);
    bool CheckCollision(shared_ptr<Ball> one, shared_ptr<GameObject> two);
    bool CheckCollision(shared_ptr<GameObject> one, shared_ptr<GameObject> two); 
    void addLevel(string path);
    void RunGame();
    bool RunLevel(string path);
};

