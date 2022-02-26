#include <iostream>

#include "paddle.hpp"

Paddle::Paddle(glm::vec2 siz,string &texture, Renderer *r)
:GameObject(glm::vec2( r-> getWidth()/2.0f - siz.x,  r-> getHeight() - siz.y), siz,texture,r)
{
}

void Paddle::updatePos(glm::vec2 pos){
    this -> pos += pos*velocity;
}