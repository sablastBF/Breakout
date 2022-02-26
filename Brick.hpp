#pragma once

#include "GameObject.hpp"

class Brick : public GameObject
{
  using GameObject::GameObject;

 private:
     /* data */
    //  string ID;
    //  int hitPoint;
     bool destroid = false, undestrojable = false;
     //string sound;

 public:
      void draw();
 };
