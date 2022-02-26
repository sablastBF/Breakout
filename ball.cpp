#include "ball.hpp"


Ball::Ball(float radius, string &text, Renderer *r): GameObject(glm::vec2(10.0f),glm::vec2(radius), text, r){
    this -> radius = radius;
}

void Ball::updatePos(){
    glm::vec2 newPos = this -> pos + this -> velocty;
    if (newPos.x < 0.0f || newPos.x + this -> radius > this -> render -> getWidth()){
        this -> velocty.x = -this -> velocty.x ;
        Ball::updatePos();
    }     

    if (newPos.y < 0.0f || newPos.y + this -> radius > this -> render -> getHeight() ){
        this -> velocty.y = -this -> velocty.y ;
        Ball::updatePos();
    }       

    this -> pos = newPos;
}


