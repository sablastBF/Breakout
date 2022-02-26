

#include <iostream>

#include "game.hpp"
#include "level.hpp"
#include "Rendere.hpp"
#include "ball.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace std;


Game::Game(unsigned int width_, unsigned int height_){

    this -> width = width_;
    this -> height = height_;
    //this -> projection = glm::ortho(0.0f, static_cast<float>( this -> width), static_cast<float>(this -> height), 0.0f, -1.0f, 1.0f);  
  
    GLFWwindow* window = crateWindow( this -> width, this -> height);
    if (!window) return ;

    this  -> render = new Renderer( this -> width, this -> height);
    // string path = "ball.png";
    // Brick *br = new Brick(glm::vec2(20.0f), glm::vec2(100.0f), path, this -> render);
    this -> level = new Level(this -> render);

    string texturePath = "padle.jpg";
    this -> paddle = new Paddle(glm::vec2(200.0f, 20.0f), texturePath, this  -> render);
    
    string texturePath1 = "background.jpg";
    this -> background = new BackGround(texturePath1, this -> render);

    string texturePath2 = "ball.png";
    this -> ball = new Ball(10.0f, texturePath2, this -> render);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        this -> draw();
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }   
}


GLFWwindow*  Game::crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Moj Lomljenje Van", NULL, NULL);
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
        this -> paddle -> updatePos(glm::vec2(-1.0f,0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        this -> paddle -> updatePos(glm::vec2(1.0f,0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
    }
}

void Game::draw(){
    this -> background -> draw();
    this -> level -> draw();
    this -> paddle -> draw();
    this -> ball -> draw();
}

bool Game::CheckCollision(){
    return false;
}