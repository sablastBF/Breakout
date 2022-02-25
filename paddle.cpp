#include <iostream>

#include "paddle.hpp"
#include "Brick.hpp"

using namespace std;


void paddle::updatePozition(glm::vec2 vec){
    glm::vec2 newPos =  this -> positionOfPadle + vec*this -> velocty;
    if (newPos.x>= 0 && newPos.x + this -> sizX  <=  this -> width)
    this -> positionOfPadle += vec*this -> velocty;
}   


void paddle::draw(){
    paddleObect -> draw(this -> positionOfPadle, glm::vec2(200.0f, 20.0f));   
}

void paddle::setupPadle(){
    this -> paddleObect = new Brick(); 
    this -> paddleObect ->  initBrickRender();
    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";

    this -> paddleObect -> setShader(shaderPathVS, shaderPathFS);

    string text = "paddle.png";
    this -> paddleObect -> setTexture(text, true);
}

paddle::paddle(){
    this -> setupPadle();
}

paddle:: paddle(unsigned int width,unsigned int height, unsigned int sizX, unsigned int sizY){
    this -> positionOfPadle =glm::vec2(width /2.0f - sizX/2.0f, height - sizY);
    this -> width = width;
    this -> height = height;

    this -> sizX = sizX;
    this -> sizY = sizY;

    this -> setupPadle();
}
