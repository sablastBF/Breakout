
#include "game.hpp"


int main(){ 
    unsigned int width_ = 800, height_ = 600;
    Game *brakeOut = new Game(width_,height_);
    brakeOut -> addLevel("levels/first.xml");
    brakeOut -> addLevel("levels/second.xml");

    brakeOut -> addLevel("levels/dragon1.xml");
    brakeOut -> addLevel("levels/dragon.xml");
    brakeOut -> RunGame();
    return 0;
}   
