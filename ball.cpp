#include "ball.hpp"


Ball::Ball(){

}

Ball::Ball(float radius, unsigned int width, unsigned int height,unsigned int sizeX, unsigned int sizeY ){
    this -> radisu = radius;
    this -> pos = glm::vec2(width/2.0f + radisu/2.0f, height - sizeY - radisu);
    this -> width = width;
    this -> height = height;
    
    this -> setUpBall();
}

void Ball::setUpBall(){
    this -> ballObject = new Brick();
    
    this -> ballObject ->  initBrickRender();

    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";

    this -> ballObject -> setShader(shaderPathVS, shaderPathFS);

    string text = "ball.png";
    this -> ballObject -> setTexture(text);

}

void Ball::draw(){
    this -> ballObject -> draw(this -> pos,glm::vec2(this-> radisu));   
}

void Ball::updatePosiztion(){
    if (this ->stuck) return ;

    glm::vec2 newPos = this -> pos + this -> velocty;
    if (newPos.x < 0.0f || newPos.x + this -> radisu > this -> width) {
        this -> velocty.x = -this -> velocty.x;
        return ;
    }
    if (newPos.y < 0.0f || newPos.y + this -> radisu > this -> height) {
        this -> velocty.y = -this -> velocty.y;
        return ;
    }

    this -> pos = newPos;
}

void Ball::updatePosiztion(glm::vec2 vector, glm::vec2 velocity){
    this -> pos += vector*velocity;
}
