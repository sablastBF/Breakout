#include <iostream>

#include "paddle.hpp"
#include "Brick.hpp"

using namespace std;


void Paddle::updatePozition(glm::vec2 vec){
    glm::vec2 newPos =  this -> positionOfPadle + vec*this -> velocty;
    if (newPos.x >= 0 && newPos.x + this -> sizX  <=  this -> width)
    this -> positionOfPadle += vec*this -> velocty;
}   


void Paddle::draw(){
    paddleObect -> draw(this -> positionOfPadle, glm::vec2(200.0f, 20.0f));   
}

void Paddle::setupPadle(){
    this -> paddleObect = new Brick(); 
    this -> paddleObect ->  initBrickRender();
    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";

    this -> paddleObect -> setShader(shaderPathVS, shaderPathFS);

    string text = "paddle.png";
    this -> paddleObect -> setTexture(text, true);
}

Paddle::Paddle(){
    this -> setupPadle();
}

Paddle::Paddle(unsigned int width,unsigned int height, unsigned int sizX, unsigned int sizY){
    this -> positionOfPadle =glm::vec2(width /2.0f - sizX/2.0f, height - sizY);
    this -> width = width;
    this -> height = height;

    this -> sizX = sizX;
    this -> sizY = sizY;

    this -> setupPadle();
}
