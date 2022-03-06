
#include "game.hpp"

Game *brakeOut = nullptr;
int main(){ 
    unsigned int width_ = 800, height_ = 600;
    brakeOut = new Game(width_,height_);
    brakeOut -> addLevel("levels/level_1.xml");
    brakeOut -> addLevel("levels/second.xml");

    brakeOut -> addLevel("levels/dragon1.xml");
    // brakeOut -> addLevel("levels/dragon.xml");
    brakeOut -> RunGame();
    return 0;
}   
