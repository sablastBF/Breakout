#include "Brick.hpp"

void Brick::draw(){
    if (this -> destroid) return ;
    GameObject::draw();
    
}

void Brick::setDistroid(){
    this -> destroid = true;
}
void Brick::resetDestroid(){
    this -> destroid = false;
}

bool Brick::getDestroid(){
    return this -> destroid;
}

unsigned int Brick::getBreakScore(){
    return this -> breakScore;
}

bool Brick::chechHit(){
    this -> hitPoint--;
    return this -> hitPoint <= 0;
}

Brick::Brick(shared_ptr<Brick> b){
    this -> textureID =  b -> textureID;
    this -> hitPoint = b -> hitPoint;
    this -> breakScore = b -> breakScore;
    this -> undestrojable = b -> undestrojable;
    this -> render = b -> render;
    this -> breakSound = b -> breakSound;
    this -> hitSound = b -> hitSound;
    this -> addBalls = b -> addBalls;
    this -> id = b -> id;
}


void Brick::playHitSound(ISoundEngine *SoundEngine){
    SoundEngine->play2D(this -> hitSound.c_str(), false);

}
void Brick::playBreakSound(ISoundEngine * SoundEngine){
    SoundEngine->play2D(this -> breakSound.c_str(), false);
}   

unsigned int Brick::gethitPoint(){return this -> hitPoint;}
void Brick::setHitPoint(unsigned int point){this -> hitPoint =point;}

string Brick::getId(){return this -> id;}
