#pragma once
#include <vector>
#include <map>
#include "Brick.hpp"


class Level
{
private:
    /* data */
    map<string, Brick *> brick;
    Renderer *rendere;
    vector<Brick *> levelBrickLayout;

public:
    Level(Renderer *rendere);
    ~Level();
    void draw();
    void loadLevelFromFile();
    void addBrick();    
};

