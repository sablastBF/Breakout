
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "game.hpp"
#include "Brick.hpp"
#include "level.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace std;

void initOpenGL();
GLFWwindow*  crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


Game::Game(unsigned int width, unsigned int height){

    projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);  
    this -> width = width;
    this -> height = height;

    GLFWwindow* window = crateWindow( width, height);
    if (!window) return ;

    // Brick *brk = new Brick();
    // brk -> setGame(this);
    // brk ->  initBrickRender();

    // string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";
    // brk -> setShader(shaderPathVS, shaderPathFS);
    // string text = "wall.jpg";
    // brk -> setTexture(text);

    Level *first= new Level(this);
    first -> loadLevelFromFile();
    first -> addBrick();
    string bacground = "background.jpg";
    first -> setBackground(bacground, );

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        first -> draw();
        // for (float x = 0.0f; x < width; x+= width/k){
        //     for (float y = 0.0f; y <= height/2.0f; y+= height/(2.0f*k)){
        //         brk -> draw(glm::vec2(x, y),glm::vec2(width/k,   height/(2.0f*k))); 
        //     }   
        // }
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }   
}



GLFWwindow*  crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
   
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}