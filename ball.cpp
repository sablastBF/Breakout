#include "ball.hpp"


Ball::Ball(float radius, string &text, Renderer *r): GameObject(glm::vec2(2.0f*radius), text, r){
    this -> radius = radius;
}

void Ball::updatePos(){
    if (this -> stuck) return ;
    
    glm::vec2 newPos = this -> pos + this -> velocty;
    if (newPos.x < 0.0f || newPos.x + this -> radius > this -> render -> getWidth()){
        this -> velocty.x = -this -> velocty.x ;
        Ball::updatePos();
    }     

    if (newPos.y < 0.0f 
    //|| newPos.y + this -> radius > this -> render -> getHeight() 
    ){
        this -> velocty.y = -this -> velocty.y ;
        Ball::updatePos();
    }       

    this -> pos = newPos;
}

float Ball::getRadius(){return this -> radius;}

void Ball::changeVelocity(){
      this -> velocty.x = -this -> velocty.x ;
    this -> velocty.y = -this -> velocty.y ;
}

void Ball::changeVelocityY(){
    this -> velocty.y = -this -> velocty.y ;
}
void Ball::changeVelocityX(){
    this -> velocty.x = -this -> velocty.x ;
}
glm::vec2 Ball::getVelocrty(){return this ->velocty;}

void Ball::setVelocrty(glm::vec2 velocty){this ->velocty = velocty;}


void Ball::flipStuck(){ this -> stuck = false;}
bool Ball::getStuck(){return this -> stuck;}

