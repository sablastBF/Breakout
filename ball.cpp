#include "ball.hpp"
#include "glm/gtc/matrix_transform.hpp"

Ball::Ball(float radius, string &text, shared_ptr<Renderer> r): GameObject(glm::vec2(2.0f*radius), text, r){
    this -> radius = radius;
}

// dodavanje novih lopta, namjenjeno je za vise lopta
Ball::Ball(shared_ptr<Ball> b, glm::vec2 velocity){
    this -> radius = b -> radius;
    this -> render = b -> render;
    this -> pos =  b -> pos;
    this -> siz = b -> siz;
    this -> velocty = velocity;
    this -> textureID = b -> textureID;
    this -> stuck = false;
    this -> offset = b -> offset;
}

bool Ball::updatePos(float dt){
    if (this -> stuck) return false;
    glm::vec2 newPos = this -> pos + this -> velocty * dt;
    if (newPos.x < this -> offset || newPos.x + this -> radius*2.0f > this -> render -> getWidth()){
        this -> velocty.x = -this -> velocty.x ;
    }     

    if (newPos.y < 0.0f){
        this -> velocty.y = -this -> velocty.y; 
    }       
    if (newPos.y + this -> radius*2.0f > this -> render -> getHeight()){
        return true;
    }

    newPos = glm::clamp(newPos, glm::vec2(this -> offset, 0.0f), glm::vec2( this -> render -> getWidth() - 2.0f*this -> radius,  this -> render -> getHeight()- 2.0f*this -> radius));

    this -> pos = newPos;
    return false;    
}
void Ball::setOffset(float offset){
    this -> offset = offset;
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


void Ball::setUnStuck(){ this -> stuck = false;}
void Ball::setStuck(){ this -> stuck = true;}

bool Ball::getStuck(){return this -> stuck;}

