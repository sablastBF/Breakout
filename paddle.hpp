#pragma once
#include "GameObject.hpp"


class Paddle: public GameObject
{
  using GameObject::GameObject;
private:
    glm::vec2 velocity = glm::vec2(1000.0f);
    float offset = 0.0f;
public:
    Paddle(glm::vec2 siz,string texture, shared_ptr<Renderer> );
    ~Paddle(){};

    void updatePos(glm::vec2, float time);
    void updateVelocty(glm::vec2 velocity);
    void restePosition();
    void setOffset(float offset);
};  

