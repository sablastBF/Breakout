#pragma once
#include <vector>
#include <map>
#include "Brick.hpp"
#include "paddle.hpp"
#include "ball.hpp"
using namespace std;

class Brick;
class paddle;
class Ball;


class Level
{
private:
    /* data */
    vector<vector<string>> levelBrickLayout;
    map<string, Brick *> brick;

    Brick *beckground = nullptr;
    paddle *padd = nullptr;
    Ball *ball = nullptr;
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
    void setPaddle(paddle *p) {this -> padd = p;}
    paddle * getPadle() {return padd;}
    Ball *getBall(){return ball;}
};

