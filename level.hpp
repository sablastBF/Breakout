#pragma once
#include <vector>
#include <map>
#include "Brick.hpp"
#include "tinyxml2.h"

class Level
{
private:
    /* data */
    map<string, Brick *> brick;
    Renderer *rendere;
    vector<Brick *> levelBrickLayout;
    GameObject *background;
public:
    Level(string path, Renderer *rendere);
    ~Level();
    void draw();
    void loadLevelFromFile(string path);
    void addBrick( tinyxml2::XMLElement *);   
    vector<Brick *> & getBricks(); 
};

