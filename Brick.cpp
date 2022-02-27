#include "Brick.hpp"


void Brick::draw(){
    if (this -> destroid) return ;
    GameObject::draw();
}

void Brick::setDistroid(){
    this -> destroid = true;
}

bool Brick::getDestroid(){
    return this -> destroid;
}