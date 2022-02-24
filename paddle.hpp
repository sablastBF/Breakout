#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"
#include "game.hpp"
#include "Brick.hpp"
using namespace std;

class paddle
{
private:
    /* data */
    glm::vec2 positionOfPadle;
    glm::vec2 velocty = glm::vec2(0.1f, 0.0f);
    Brick *paddleObect = nullptr;
    Game *game = nullptr;

public:
    paddle(/* args */);
    paddle(Game *);
    ~paddle();
    
    void updatePozition( );
    void draw();
    void setupPadle();
    void setGame(Game *game ){this -> game = game;}
};

