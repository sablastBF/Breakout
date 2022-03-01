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
    
  public:
      Brick(Brick *);

      void draw();
      void setDistroid();
      bool getDestroid();
      bool getUndestrojable();
      unsigned int getBreakScore();
      bool chechHit();
      void setHit(unsigned int hit){this -> hitPoint = hit;}
      void setBreakScore(unsigned int breakScore){this -> breakScore = breakScore;}
      void setBreakSound(string bs){this -> breakSound = bs;}
      void setHitSound(string hs){this -> hitSound = hs;}
      void playHitSound(ISoundEngine *SoundEngine);
      void playBreakSound(ISoundEngine *SoundEngine);
 };
