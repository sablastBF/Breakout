#include "ball.hpp"


Ball::Ball(float radius, string &text, Renderer *r): GameObject(glm::vec2(radius), glm::vec2(10.0f), text, r){
}

