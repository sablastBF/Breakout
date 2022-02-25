#pragma once

#include "Brick.hpp"


class Brick;

class Ball{
    private:
    glm::vec2 pos;
    glm::vec2 velocty = glm::vec2(-10.0f, -10.0f);
    float radisu;
    Brick *ballObject;
    unsigned int width, height;
    bool stuck = true;

    public:

    Ball();
    Ball(glm::vec2 pos,float r, unsigned int width, unsigned int height);
    void updatePosiztion();
    void setUpBall();
    void draw();
    bool getStuck(){return stuck;}
};