#pragma once
#include <vector>
#include <map>
#include <memory>
#include "Brick.hpp"
#include "tinyxml2.h"
#include "ball.hpp"
#include "paddle.hpp"

class Level
{
private:
    /* data */
    map<string, shared_ptr<Brick>> brick;
    shared_ptr<Renderer> render = nullptr;
    vector<shared_ptr<Brick>> levelBrickLayout;

    shared_ptr<GameObject> background = nullptr;
    shared_ptr<Paddle> paddle = nullptr;
    vector<shared_ptr<Ball>> balls;

    // tu bih trebao dodati lopti i padle, nekako mi je logicnije
public:
    Level(string path, shared_ptr<Renderer> render);
    Level(string path, unsigned int textureID,shared_ptr<Renderer> render, shared_ptr<Renderer> BrickRender);

    ~Level(){};
    void draw();
    void loadLevelFromFile(string path);
    void addBrick( tinyxml2::XMLElement *);   
    vector<shared_ptr<Brick>> & getBricks();
    
    shared_ptr<Paddle> getPaddle() {return paddle;}
    shared_ptr<Ball> getBall() {return balls[0];}
    void setBallPositionStuck();
    void addBalls(shared_ptr<Ball> ball, unsigned int N);
    vector<shared_ptr<Ball> > & getBalls();

    void reste();
    
};

