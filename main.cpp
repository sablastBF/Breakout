
#include "game.hpp"


int main(){ 
    unsigned int width_ = 894/1.5, height_ = 1201/1.5;
    Game *brakeOut = new Game(width_,height_);
    brakeOut -> addLevel("levels/dragon1.xml");
    brakeOut -> addLevel("levels/dragon.xml");
    brakeOut -> RunGame();
    return 0;
}   
