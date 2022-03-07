
#include "Rendere.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.hpp"

using namespace  std;


void Renderer::draw(glm::vec2 pos,glm::vec2 siz,  unsigned int textureID){

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    this -> brickShader.use();
    this -> brickShader.setMat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f)), glm::vec3(siz, 0.0f)));
    this -> brickShader.setMat4("projection", this -> projection);

    glBindVertexArray(this -> bickVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void Renderer::initRender(){
    float vertices[] = { 
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };


    unsigned int indices[] = { 
        0, 1, 3,  
        0, 2, 3  
    };
      
    glGenVertexArrays(1, &this -> bickVAO);

    glGenBuffers(1, &this -> VBO);
    glGenBuffers(1, &this -> EBO);
    glBindVertexArray(this -> bickVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this -> VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}


void Renderer::setShader(string &vertexPath, string &fragmetPath){
    this -> brickShader = Shader(vertexPath.c_str(), fragmetPath.c_str());
    this -> brickShader.use();
}   



Renderer::Renderer(unsigned int width, unsigned int height, string pathVS, string pathFS){
    this -> width = width;
    this -> height = height;

    this -> initRender();
    //string shaderPathVertex = "shaders/basic_brick.vs",shaderPathFragment =  "shaders/basic_brick.fs";
    this -> setShader(pathVS, pathFS);
    this -> projection = glm::ortho(0.0f, static_cast<float>( width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
}

unsigned int Renderer::getHeight(){
    return this -> height;
}


unsigned int Renderer::getWidth(){
    return this -> width;
}


