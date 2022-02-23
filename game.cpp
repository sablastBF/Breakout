#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "game.hpp"
#include "Brick.hpp"


using namespace std;

void initOpenGL();
GLFWwindow*  crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);


Game::Game(unsigned int width, unsigned int height){

   GLFWwindow* window = crateWindow( width, height);
    if (!window) return ;

    Brick *brk = new Brick();
    brk ->  initBrickRender();

    string shaderPathVS = "shaders/basic_brick.vs", shaderPathFS = "shaders/basic_brick.fs";
    brk -> setShader(shaderPathVS, shaderPathFS);
    string text = "wall.jpg";
    brk -> setTexture(text);


    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        brk -> draw();
     
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return nullptr;
    }    

    return window;
}

