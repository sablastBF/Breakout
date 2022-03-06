#pragma once
#include <memory>
#include "Rendere.hpp"

class GameObject
{
protected:
    /* data */
    glm::vec2 pos, siz;
    shared_ptr<Renderer> render;
    GLuint textureID;

public:
    GameObject();
    GameObject(string &textureID, shared_ptr<Renderer> render);
    GameObject( glm::vec2 siz, string textureID, shared_ptr<Renderer> render);
    GameObject(glm::vec2 pos, glm::vec2 siz, string textureID, shared_ptr<Renderer> render);
    GameObject(shared_ptr<GameObject>);
    ~GameObject(){};
    void draw();
    void loadTexture(string &path);
    void setPos(glm::vec2);
    void setSiz(glm::vec2);
    glm::vec2 getPos();
    glm::vec2 getSiz();
};

