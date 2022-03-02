#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "GameObject.hpp"

void GameObject::draw(){
    this -> render -> draw(this -> pos, this -> siz, this -> textureID);
}

GameObject::GameObject(){
}

GameObject::GameObject(string &texturePath, Renderer *render){
    this -> loadTexture(texturePath);
    this -> render = render;
}

GameObject::GameObject( glm::vec2 siz, string &texturePath, Renderer *render){
    this -> siz = siz;
    this -> loadTexture(texturePath);
    this -> render = render;
}


GameObject::GameObject(glm::vec2 pos, glm::vec2 siz, string &texturePath, Renderer *render){
    this -> pos = pos;
    this -> siz = siz;
    this -> loadTexture(texturePath);
    this -> render = render;
}

GameObject::GameObject(GameObject * cop){
    // this -> pos = cop -> pos;
    // this -> siz = cop -> siz;
    this -> textureID = cop -> textureID;
    this -> render = cop -> render;
}

void GameObject::setPos(glm::vec2 pos){
    this -> pos = pos;
}

void GameObject::setSiz(glm::vec2 siz){
    this -> siz = siz;
}

void GameObject::loadTexture(string &path){
    glGenTextures(1, &this ->textureID);
    glBindTexture(GL_TEXTURE_2D, this ->textureID); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
    int width, height, nrChannels;
    unsigned char *data = nullptr;
 
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (data)
    {
        if (path.substr(path.find_last_of(".") + 1) == "png"){
            glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else { 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

glm::vec2 GameObject::getPos() {return this -> pos;}
glm::vec2 GameObject::getSiz() {return this -> siz;}

