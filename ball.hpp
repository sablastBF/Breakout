#pragma once
#include "GameObject.hpp"

class Ball: public GameObject{
    using GameObject::GameObject;

    private:
        glm::vec2 velocty = glm::vec2(0.0f, -400.0f);
        float radius;
        bool stuck = true;

    public:

    Ball(float radius, string &text, Renderer *r);
    void updatePos(float dt);
    void flipStuck();
    bool getStuck();
    float getRadius();
    void changeVelocity();
    void changeVelocityY();
    void changeVelocityX();
    void setVelocrty(glm::vec2 velocty);
    glm::vec2 getVelocrty();

};