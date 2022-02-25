#pragma once

#include "Brick.hpp"


class Brick;

class Ball{
    private:
    glm::vec2 pos;
    glm::vec2 velocty = glm::vec2(-5.0f, -5.0f);
    float radisu;
    Brick *ballObject;
    unsigned int width, height;
    bool stuck = true;

    public:

    Ball();
    Ball(float r, unsigned int width, unsigned int height);
        Ball(float r, unsigned int width, unsigned int height, unsigned int sizeX, unsigned int sizeY);

    void updatePosiztion();
    void updatePosiztion(glm::vec2,glm::vec2 );

    void setUpBall();
    void draw();
    bool getStuck(){return stuck;}
    void flipStuck(){stuck = false;}
};