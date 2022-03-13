#include "game.hpp"

Game *brakeOut = nullptr;

int main(){ 
    unsigned int width = 1200, height = 900;
    brakeOut = new Game(width, height);

    brakeOut -> addLevel("resources/levels/level_1.xml");
    brakeOut -> addLevel("resources/levels/level_2.xml");
    brakeOut -> addLevel("resources/levels/level_3.xml");
    brakeOut -> addLevel("resources/levels/level_4.xml");
    brakeOut -> addLevel("resources/levels/level_5.xml");

    brakeOut -> runGame();
    return 0;
}   
