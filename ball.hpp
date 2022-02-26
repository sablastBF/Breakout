#pragma once
#include "GameObject.hpp"

class Ball: public GameObject{
    using GameObject::GameObject;

    private:
        glm::vec2 velocty = glm::vec2(-5.0f, -5.0f);
        float radisu;
        bool stuck = true;

    public:

    Ball(float radius, string &text, Renderer *r);
};