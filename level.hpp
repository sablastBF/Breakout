#pragma once
#include <vector>
#include <map>
#include "Brick.hpp"

using namespace std;

class Brick;
class Paddle;
class Ball;


class Level
{
private:
    /* data */
    vector<vector<string>> levelBrickLayout;
    map<string, Brick *> brick;

    Brick *beckground = nullptr;

    unsigned int width; 
    unsigned int height;
    

public:
    Level(/* args */){}
    Level(unsigned int width, unsigned int height);
    ~Level();
    void draw();
    void loadLevelFromFile();
    void addBrick();
    void drawBackground();
    void setBackground(string &path);
    
};

