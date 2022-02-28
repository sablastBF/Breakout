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

bool Brick::getUndestrojable(){
    return this -> undestrojable;
}

unsigned int Brick::getBreakScore(){
    return this -> breakScore;
}

bool Brick::chechHit(){
    cout <<"DASSDASDSAS"<<" "<<this -> hitPoint<<endl;
    this -> hitPoint--;
    return this -> hitPoint <= 0;
}
void Brick::setBrickParameters(unsigned int breakScore, unsigned int hitPoints){
    this -> breakScore = breakScore;
    this -> hitPoint = hitPoint;
    cout << "ASDSA"<< " "<<this -> hitPoint<< endl;
}

