#pragma once
#include <vector>
#include "GameObject.hpp"

class Ball: public GameObject{
    using GameObject::GameObject;

    private:
        glm::vec2 velocty = glm::vec2(0.0f, -400.0f);
        float radius;
        bool stuck = true;
        vector<float> path;
        unsigned int lineVAO;
        unsigned int lineVBO, lineEBO;
        Shader lineShader;
    public:

    Ball(float radius, string &text, shared_ptr<Renderer> r);
    Ball(shared_ptr<Ball> b, glm::vec2 velocity);

    void updatePos(float dt);
    void flipStuck();
    bool getStuck();
    float getRadius();
    void changeVelocity();
    void changeVelocityY();
    void changeVelocityX();
    void drawLinePath();
    void setVelocrty(glm::vec2 velocty);
    glm::vec2 getVelocrty();

};