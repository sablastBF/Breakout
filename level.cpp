#include <stb_image.h>
#include <vector>

#include "level.hpp"
#include "shader.hpp"
#include "paddle.hpp"
#include "ball.hpp"

void Level::draw(){

    this -> drawBackground();

    float width_ =  static_cast<float>(this -> width)/ static_cast<float>(this -> levelBrickLayout.size());
    float height_ = static_cast<float>(this -> height) / (2.0f*static_cast<float>(this -> levelBrickLayout[0].size()));
    float minSquare = min(width_, height_);
    minSquare = width_;

    for (float i = 0; i < this -> levelBrickLayout.size(); i++){
        for (float j = 0; j < this -> levelBrickLayout[0].size(); j++){
            if (this -> brick.find(this -> levelBrickLayout[i][j]) != this -> brick.end())
            this -> brick[this -> levelBrickLayout[i][j]] -> draw(glm::vec2(i * width_ , j*width_) ,glm::vec2(width_ , width_));   
        }
    }    
}

void Level::loadLevelFromFile(){
    int n = 15, m = 5;
    this -> levelBrickLayout.resize(n, vector<string>(m, "1"));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if ((i % 2 && j % 2) || (i % 2 == 0 && j % 2 == 0))
            this -> levelBrickLayout[i][j] = "0"; 
        }
    }
}


void Level::addBrick(){
    Brick *brk = new Brick();
    brk ->  initBrickRender();
    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";
    brk -> setShader(shaderPathVS, shaderPathFS);
    string text = "block.png";
    brk -> setTexture(text);
    this -> brick["1"] = brk;
}

void Level::setBackground(string &path){

    this -> beckground = new Brick();
    this -> beckground ->  initBrickRender();
    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";
    this -> beckground -> setShader(shaderPathVS, shaderPathFS);
    this -> beckground -> setTexture(path);

}   

void Level::drawBackground(){
    this -> beckground ->draw(glm::vec2(0.0f, 0.0f), glm::vec2(this -> width , this -> height));
}


Level::Level(unsigned int width, unsigned int height){
    this -> width = width;
    this -> height = height;
    
    string pathBackground = "background.jpg";
    this -> setBackground(pathBackground);
    this -> addBrick();
    this -> loadLevelFromFile();
}


