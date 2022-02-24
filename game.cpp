

#include <iostream>

#include "game.hpp"
#include "Brick.hpp"
#include "level.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace std;


Game::Game(unsigned int width, unsigned int height){

    projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);  
    this -> width = width;
    this -> height = height;

    GLFWwindow* window = crateWindow( width, height);
    if (!window) return ;

    Level *first= new Level(this);
    first -> loadLevelFromFile();
    first -> addBrick();
    string bacground = "background.jpg";
    first -> setBackground(bacground);

    paddle *pa = new paddle(this);
    pa -> setupPadle();
    first -> setPaddle(pa);
    
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        first -> draw();
      
      
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
        cout <<"LEVO" << endl;
    }

     if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        cout <<"DESNO" << endl;
    }
}