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
    this -> hitPoint--;
    return this -> hitPoint <= 0;
}

Brick::Brick(Brick *b){
    this -> textureID =  b -> textureID;
    this -> hitPoint = b -> hitPoint;
    this -> breakScore = b -> breakScore;
    this -> undestrojable = b -> undestrojable;
    this -> render = b -> render;
    this -> breakSound = b -> breakSound;
    this -> hitSound = b -> hitSound;
}


void Brick::playHitSound(ISoundEngine *SoundEngine){
    cout << this -> hitSound << endl;
    SoundEngine->play2D(this -> hitSound.c_str(), false);

}
void Brick::playBreakSound(ISoundEngine *SoundEngine){
    cout << this -> breakSound << endl;
    SoundEngine->play2D(this -> breakSound.c_str(), false);

}   