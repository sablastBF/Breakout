#pragma once
#include <vector>
#include <map>
#include "Brick.hpp"
#include "paddle.hpp"
#include "game.hpp"
using namespace std;

class Level
{
private:
    /* data */
    vector<vector<string>> levelBrickLayout;
    map<string, Brick *> brick;
    Game *game;
    Brick *beckground = nullptr;
    paddle *padd = nullptr;

public:
    Level(/* args */){}
    Level(Game *game) {this -> game = game;}
    ~Level();
    void draw();
    void loadLevelFromFile();
    void addBrick();
    void drawBackground();
    void setBackground(string &path);
    void setPaddle(paddle *p) {this -> padd = p;}
};

