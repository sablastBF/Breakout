#include <stb_image.h>
#include <vector>

#include "level.hpp"
#include "tinyxml2.h"
#include "shader.hpp"
#include "paddle.hpp"


void Level::draw(){
    this -> drawBackground();

    float width =  static_cast<float>(this -> game -> getWidth())/ static_cast<float>(this -> levelBrickLayout.size());
    float height = static_cast<float>(this -> game -> getHeight()) / (2.0f*static_cast<float>(this -> levelBrickLayout[0].size()));
    float minSquare = min(width, height);
    minSquare = width;

    for (float i = 0; i < this -> levelBrickLayout.size(); i++){
        for (float j = 0; j < this -> levelBrickLayout[0].size(); j++){
            this -> brick[this -> levelBrickLayout[i][j]] -> draw(glm::vec2(i * width , j*height) ,glm::vec2(width , height));   
        }
    }
    
    padd -> draw();
}

void Level::loadLevelFromFile(){
    int n = 15, m = 5;
    this -> levelBrickLayout.resize(n, vector<string>(m, "1"));
}


void Level::addBrick(){
    Brick *brk = new Brick();
    brk -> setGame(this -> game);
    brk ->  initBrickRender();
    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";
    brk -> setShader(shaderPathVS, shaderPathFS);
    string text = "block.png";
    brk -> setTexture(text);
    this -> brick["1"] = brk;
}

void Level::setBackground(string &path){
    this -> beckground = new Brick();
    this -> beckground -> setGame(this -> game);
    this -> beckground ->  initBrickRender();
    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";
    this -> beckground -> setShader(shaderPathVS, shaderPathFS);
    this -> beckground -> setTexture(path);
}   

void Level::drawBackground(){
    this -> beckground ->draw(glm::vec2(0.0f, 0.0f), glm::vec2(this -> game -> getWidth(), this -> game -> getHeight()));
}

