#include "BackGround.hpp"


BackGround::BackGround(string &text, Renderer *r)
: GameObject(glm::vec2(0,0), glm::vec2(r ->getWidth(), r -> getHeight()) , text, r){}