#include <iostream>

#include "paddle.hpp"

Paddle::Paddle(glm::vec2 siz,string &texture,  shared_ptr<Renderer> r)
:GameObject(glm::vec2( r-> getWidth()/2.0f - siz.x/2.0f,  r-> getHeight() - siz.y), siz,texture,r)
{
}

void Paddle::updatePos(glm::vec2 direction, float dt){
    glm::vec2 newPos =   this -> pos + direction*velocity * dt;
    this -> pos = glm::clamp(newPos,glm::vec2(0.0f,0.0f), glm::vec2(this -> render -> getWidth() -this -> siz.x , this -> render -> getHeight()));
}

void Paddle::updateVelocty(glm::vec2 velocity){
    this -> velocity = velocity;
}