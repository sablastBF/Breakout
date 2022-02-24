#include "paddle.hpp"
#include "Brick.hpp"
#include <iostream>

using namespace std;

void paddle::updatePozition(){
    cout << "Asdas"<<endl;
}   


void paddle::draw(){
    cout <<"ASD"<<endl;
    paddleObect -> draw(this -> positionOfPadle, glm::vec2(100.0f, 10.0f));   
}

void paddle::setupPadle(){
    this -> paddleObect = new Brick(); 
    this -> paddleObect -> setGame(this -> game);

    positionOfPadle = glm::vec2(this -> game -> getWidth()/2.0f, this -> game -> getHeight() - 10.0f);

    this -> paddleObect ->  initBrickRender();

    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";

    this -> paddleObect -> setShader(shaderPathVS, shaderPathFS);

    string text = "paddle.png";
    this -> paddleObect -> setTexture(text, true);

}


paddle::paddle(Game *game){
    this -> setGame(game);
    this -> setupPadle();
}