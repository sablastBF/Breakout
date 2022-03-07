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
    shared_ptr<GameObject> backgroundLevel = nullptr;

    shared_ptr<Paddle> paddle = nullptr;
    vector<shared_ptr<Ball>> balls;
    unsigned int numberOfBalls = 1, numberOfBricks = 0;
    unsigned int numberOfBricksOriginal;
    unsigned int tezina = 1;
    float offset;
    unsigned int liveNumber = 0;
    // tu bih trebao dodati lopti i padle, nekako mi je logicnije
public:
    Level(string path, shared_ptr<Renderer> render);

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
    bool isGameWon();
    void distorjBrick();
    void distorjBall();
    bool doesGameHaveBall();
    void decreseLive();

    unsigned int getTezina(){return this -> tezina;}
    unsigned int getNumberOfBalls(){return this -> numberOfBalls;}
    unsigned int getNumberOfBricks(){return this -> numberOfBricksOriginal;}
    unsigned int getNumberOFLives(){return liveNumber;}
    unsigned int getNumberOfDistroid(){return numberOfBricksOriginal -numberOfBricks;}
};

