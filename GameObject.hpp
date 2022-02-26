#pragma once
#include "Rendere.hpp"

class GameObject
{
protected:
    /* data */
    glm::vec2 pos, siz;
    Renderer *render;
    
private:
    unsigned int textureID;

public:
    GameObject();
    GameObject(string &textureID, Renderer *render);
    GameObject(glm::vec2 pos, glm::vec2 siz, string &textureID, Renderer *render);
    GameObject(GameObject*);
    ~GameObject(){};
    void draw();
    void loadTexture(string &path);
    void setPos(glm::vec2);
    void setSiz(glm::vec2);
};

