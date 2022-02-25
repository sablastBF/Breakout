#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Brick.hpp"
#include "game.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.hpp"

using namespace  std;

float k = 0.0f;
glm::mat4 model = glm::mat4(1.0f);

void Brick::draw(glm::vec2 pos,glm::vec2 siz){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this -> brickTexture);
    this -> brickShader.use();
    glm::mat4 mo = model;

    mo = glm::translate(mo, glm::vec3(pos, 0.0f));
    mo = glm::scale(mo, glm::vec3(siz, 0.0f));

    this -> brickShader.setMat4("model", mo);
    this -> brickShader.setMat4("projection", 
    glm::ortho(0.0f, static_cast<float>( 800), static_cast<float>(600), 0.0f, -1.0f, 1.0f)
    );

    glBindVertexArray(this -> bickVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void Brick::initBrickRender(){
    float vertices[] = { 
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
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

void Brick::loadFromFile(){

}

void Brick::setShader(string &vertexPath, string &fragmetPath){

    this -> brickShader = Shader(vertexPath.c_str(), fragmetPath.c_str());
    this -> brickShader.use();
}   

void Brick::setTexture(string &path, bool alpha){
    
    glGenTextures(1, &this -> brickTexture);
    glBindTexture(GL_TEXTURE_2D, this -> brickTexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(),&width, &height, &nrChannels, 0);
    cout <<path<<endl;
    if (data)
    {
        if (alpha){

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        cout << path << endl;
        }
        else 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Brick::Brick(){

}   

