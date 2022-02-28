#pragma once
#include "GameObject.hpp"


class Paddle: public GameObject
{
  using GameObject::GameObject;
private:
    glm::vec2 velocity = glm::vec2(1000.0f);
public:
    Paddle(glm::vec2 siz,string &texture, Renderer *);
    ~Paddle(){};

    bool updatePos(glm::vec2, float time);
    void updateVelocty(glm::vec2 velocity);

};  

