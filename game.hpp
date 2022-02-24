#pragma once
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"

class Game
{
private:
    //map<string, unsigned int> popisTekstura; 
    glm::mat4 projection;
    unsigned int width, height;


public:

    Game(unsigned int width, unsigned int height);
    ~Game();

    unsigned int getWidth(){return width;}
    unsigned int getHeight(){return height;}
    glm::mat4 getProjection(){return projection;}
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
    GLFWwindow*  crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
};

