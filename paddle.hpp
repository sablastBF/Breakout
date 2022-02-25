#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"
#include "Brick.hpp"

class Brick;

class Paddle
{
private:
    /* data */
    glm::vec2 positionOfPadle;
    glm::vec2 velocty = glm::vec2(10.0f, 0.0f);
    Brick *paddleObect = nullptr;
    unsigned int sizX, sizY;
    unsigned int width, height;

public:
    Paddle(/* args */);
    Paddle(unsigned int width,unsigned int height, unsigned int sizX, unsigned int sizY);

    ~Paddle();
    
    void updatePozition(glm::vec2 );
    void draw();
    void setupPadle();
    glm::vec2 getVelocty(){return velocty;}

};

