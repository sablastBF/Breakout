#pragma once

#include <string>
#include "shader.hpp"

using namespace std;


class Renderer
 {
 private:
     /* data */
    unsigned int bickVAO;
    unsigned int VBO, EBO;
    Shader brickShader;
    glm::mat4 model = glm::mat4(1.0f), projection;
    unsigned int width, height;

 public:
    Renderer(unsigned int width, unsigned int height, string pathVS, string pathFS);

    ~Renderer(){};
    void initRender();
    void draw(glm::vec2,glm::vec2, unsigned int );

    void setShader(string &,  string & );
    void setTexture(string &, bool alpfha = false);
    void setProjectionMatrix(unsigned int width,unsigned int hegiht );
    //void setSize(unsigned int width,unsigned int height );
    glm::mat4 getProjection(){return projection;}
    unsigned int getWidth();
    unsigned int getHeight();
 };
