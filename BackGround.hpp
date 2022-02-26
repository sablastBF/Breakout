#pragma once
#include "GameObject.hpp"

class BackGround : public GameObject
{
    using GameObject::GameObject;

public:
    BackGround(string &text, Renderer *r);
    ~BackGround(){};
};

