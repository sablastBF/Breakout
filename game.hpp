#pragma once

#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"
#include "level.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "Rendere.hpp"
#include "BackGround.hpp"

class Game
{
private:
    //map<string, unsigned int> popisTekstura; 
    glm::mat4 projection;
    unsigned int width, height;
    Level *level = nullptr;
    Ball *ball;
    Paddle *paddle;
    Renderer *render;
    BackGround *background;
    
public:

    Game(unsigned int width_, unsigned int height_);
    ~Game();

    static void framebuffer_size_callback(GLFWwindow* window, int width_, int height_);
    void processInput(GLFWwindow *window);
    GLFWwindow*  crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    
    unsigned int getWidth(){return width;}
    unsigned int getHeight(){return height;}
    glm::mat4 getProjection(){return projection;}
    bool CheckCollision();
    void DoCollison();
    void draw();
};

