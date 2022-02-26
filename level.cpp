#include <stb_image.h>
#include <vector>

#include "level.hpp"
#include "shader.hpp"
#include "paddle.hpp"
#include "ball.hpp"

void Level::draw(){
    for (Brick *b: this -> levelBrickLayout) b -> draw();
}

void Level::loadLevelFromFile(){
    int n = 100, m = 10;
   
    float width_ =  static_cast<float>(this -> rendere -> getWidth())/ static_cast<float>(n);
    float height_ = static_cast<float>(this -> rendere -> getHeight()) / (2.0f*static_cast<float>(m));
    float minSquare = min(width_, height_);
    minSquare = width_;
    Brick *b = this ->brick["1"];
    for (float i = 0; i < n; i++){
        for (float j = 0; j < m; j++){
           Brick *br = new Brick(b);
           br -> setPos(glm::vec2(width_ * i, height_ * j ));
           br -> setSiz(glm::vec2(width_, height_));
           this -> levelBrickLayout.push_back(br);
        }
    } 
}

void Level::addBrick(){
    string txt = "block.png";
    Brick *brk = new Brick(txt, this -> rendere);
    this -> brick["1"] = brk;
}

Level::Level(Renderer *rendere){
    this -> rendere = rendere;
    this -> addBrick();
    this -> loadLevelFromFile();
}
