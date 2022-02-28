#pragma once

#include "GameObject.hpp"

class Brick : public GameObject
{
  using GameObject::GameObject;

 private:
     /* data */
     int hitPoint = 0, breakScore = 0;
     bool destroid = false, undestrojable = false;
     //string sound;
    
 public:
      Brick(Brick *);

      void draw();
      void setDistroid();
      bool getDestroid();
      bool getUndestrojable();
      unsigned int getBreakScore();
      bool chechHit();
      void setBrickParameters(unsigned int breakScore, unsigned int hitPoints);

 };
