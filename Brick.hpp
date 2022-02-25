#pragma once

#include <string>
#include "shader.hpp"
#include "level.hpp"

using namespace std;


class Brick
 {
 private:
     /* data */
    unsigned int bickVAO;
    unsigned int VBO, EBO;
    Shader brickShader;
    unsigned int brickTexture;
    bool distroid = false;
    unsigned int posX, posY, sizeX, sizeY;

 public:
    Brick(/* args */);
    Brick(  unsigned int posX, unsigned int posY, unsigned int sizeX,  unsigned int sizeY);

    ~Brick();
    void initBrickRender();
    void loadFromFile();
    void draw(glm::vec2,glm::vec2);

    void setShader(string &,  string & );
    void setTexture(string &, bool alpfha = false);
 };
