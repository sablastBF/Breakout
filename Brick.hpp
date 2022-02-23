#pragma once

#include "shader.hpp"
#include <string>

using namespace std;

class Brick
 {
 private:
     /* data */
    unsigned int bickVAO;
     unsigned int VBO, EBO;
    Shader brickShader;
    unsigned int brickTexture;

 public:
     Brick(/* args */);
     ~Brick();
    void initBrickRender();
    void loadFromFile();
    void draw();

    void setShader(string &vertexPath,  string &fragmetPath );
    void setTexture(string &path);
 };
