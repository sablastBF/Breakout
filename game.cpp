

#include <iostream>

#include "game.hpp"
#include "Brick.hpp"
#include "level.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace std;


Game::Game(unsigned int width_, unsigned int height_){

    this -> width = width_;
    this -> height = height_;
    //this -> projection = glm::ortho(0.0f, static_cast<float>( this -> width), static_cast<float>(this -> height), 0.0f, -1.0f, 1.0f);  

    GLFWwindow* window = crateWindow(  this -> width, this -> height);
    if (!window) return ;

    this -> level = new Level(width_, height_);
    

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        this -> level -> draw();
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }   
}


GLFWwindow*  Game::crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return nullptr;
    }    

    return window;
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{   
    glViewport(0, 0, width, height);
}

void Game::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        this -> level -> getPadle() -> updatePozition(glm::vec2(-1.0f,0.0f));
        if (this -> level -> getBall() -> getStuck()){
            //this -> level -> getBall() -> updatePosiztion(glm::vec2(-1.0f,0.0f));
        }
    }

     if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        this -> level -> getPadle() -> updatePozition(glm::vec2(1.0f,0.0f));
        if (this -> level -> getBall() -> getStuck()){
           // this -> level -> getBall() -> updatePosiztion(glm::vec2(1.0f,0.0f));
        }
    }
}