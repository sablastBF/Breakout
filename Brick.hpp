#pragma once

#include "GameObject.hpp"
#include <irrklang/irrKlang.h>
using namespace irrklang;

class Brick : public GameObject
{
  using GameObject::GameObject;

  private:
     /* data */
     unsigned int hitPoint = 0, breakScore = 1;
     bool destroid = false, undestrojable = false;
     string breakSound, hitSound;
     unsigned int addBalls = 0;
    
  public:
      Brick(shared_ptr<Brick> );

      void draw();
      void setDistroid();
      bool getDestroid();
      bool getUndestrojable(){return this -> undestrojable;}
      void setUndestrojable(bool state){this -> undestrojable = state;}
      void setNumberOfBalls(unsigned int addBalls){this -> addBalls = addBalls;}
      unsigned int getNumberOfBalls(){return this -> addBalls;}
      unsigned int getBreakScore();
      bool chechHit();
      void setHit(unsigned int hit){this -> hitPoint = hit;}
      void setBreakScore(unsigned int breakScore){this -> breakScore = breakScore;}
      void setBreakSound(string bs){this -> breakSound = bs;}
      void setHitSound(string hs){this -> hitSound = hs;}
      void playHitSound(ISoundEngine * SoundEngine);
      void playBreakSound(ISoundEngine * SoundEngine);

      void resetDestroid();

 };
