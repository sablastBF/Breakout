#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "glm/gtc/matrix_transform.hpp"
#include "shader.hpp"
#include "Brick.hpp"

using namespace  std;

float k = 0.0f;
void Brick::draw(){

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this -> brickTexture);

    this -> brickShader.use();
    glBindVertexArray(this -> bickVAO);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f);  

    // model = glm::rotate(model, k, glm::vec3(0.0f, 0.0f, 1.0f)); 
    // k+=0.1f;
        
    this -> brickShader.setMat4("model", model);
    this -> brickShader.setMat4("projection", projection);


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void Brick::initBrickRender(){
       float vertices[] = { 
        // pos      // tex
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };


    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        0, 2, 3   // second Triangle
    };
   
    glGenVertexArrays(1, &this -> bickVAO);
    glGenBuffers(1, &this -> VBO);
    glGenBuffers(1, &this -> EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(this -> bickVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this -> VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

void Brick::loadFromFile(){

}

void Brick::setShader(string &vertexPath, string &fragmetPath){

    this -> brickShader = Shader(vertexPath.c_str(), fragmetPath.c_str());
    this -> brickShader.use();
}   

void Brick::setTexture(string &path){
    
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
    if (data)
    {
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

