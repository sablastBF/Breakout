#include <stb_image.h>
#include <vector>
#include "string"

#include "level.hpp"

using namespace tinyxml2;

void Level::draw(){
    this -> background -> draw();
    for (Brick *b: this -> levelBrickLayout) b -> draw();
}

void Level::loadLevelFromFile(string path){

    unsigned int n = 20, m = 20;
    unsigned int spacC = 20, rowC = 20;

    string pathBackground;
    XMLDocument levelXml;
    levelXml.LoadFile(path.c_str());

    tinyxml2::XMLElement* levelData = levelXml.FirstChild()->ToElement();
    levelData->FindAttribute("RowCount")->QueryUnsignedValue(&m);
    levelData->FindAttribute("ColumnCount")->QueryUnsignedValue(&n);
    levelData->FindAttribute("RowSpacing")->QueryUnsignedValue(&rowC);

    levelData->FindAttribute("ColumnSpacing")->QueryUnsignedValue(&spacC);
    pathBackground = levelData->FindAttribute("BackgroundTexture")->Value();

    this -> background = new GameObject(glm::vec2(0.0f), glm::vec2(this -> rendere -> getWidth(), this -> rendere -> getHeight() ),pathBackground, this -> rendere);
    //pElement->FindAttribute("RowCount")->QueryUnsignedValue(&k);
    
    float width_ =  static_cast<float>(this -> rendere -> getWidth())/ static_cast<float>(n);
    float height_ = static_cast<float>(this -> rendere -> getHeight()) / (3.0f/2.0f*static_cast<float>(m));
    float minSquare = min(width_, height_);
    minSquare = width_;

// dodajemo vrste brkova
    XMLElement * brickS = levelData -> FirstChildElement("BrickTypes");
    brickS = brickS -> FirstChildElement("BrickType");

    while(brickS != nullptr){
        this -> addBrick(brickS);
        brickS = brickS -> NextSiblingElement("BrickType");
    }

    string levelOtline = levelData->FirstChildElement("Bricks")->GetText();

    vector<string> v;
    string levelID;
    for (int i = 0; i < levelOtline.length(); i++){
        if (levelOtline[i] == '\t' || levelOtline[i] == '\n'|| levelOtline[i] == ' '){
            if (!levelID.empty())
            v.push_back(levelID);
            levelID.clear();
        } else {
            levelID.push_back(levelOtline[i]);
        }
    }
    if (!levelID.empty())
    v.push_back(levelID);
    
    int k = 0;
    for (float i = 0; i < m; i++){
        for (float j = 0; j < n; j++){
           if (this -> brick.find(v[k]) == this -> brick.end()) {k++;continue;}
           Brick *br = new Brick(this -> brick[v[k++]]);
           br -> setPos(glm::vec2(width_ * j, height_ * i ));
           br -> setSiz(glm::vec2(width_, height_));
           this -> levelBrickLayout.push_back(br);
        }
    } 
}

void Level::addBrick( XMLElement * brick){

    string id = brick->FindAttribute("Id")->Value();
    string texturePath = brick->FindAttribute("Texture")->Value();
    unsigned int hitPoints;
    brick->FindAttribute("HitPoints")->QueryUnsignedValue(&hitPoints);
    string soundPath = brick->FindAttribute("BreakSound")->Value();
    unsigned int breakScore;
    brick->FindAttribute("BreakScore")->QueryUnsignedValue(&breakScore);

    string txt = "block.jpg";
    Brick *brk = new Brick(txt, this -> rendere);
    brk -> setHit(hitPoints);
    brk -> setBreakScore(breakScore);
    brk -> setBreakSound(soundPath);
    brk -> setHitSound(soundPath);

    this -> brick[id] = brk;
}

Level::Level(string path,Renderer *rendere){
    this -> rendere = rendere;
    this -> loadLevelFromFile(path);
}

vector<Brick *> &  Level::getBricks(){
    return this -> levelBrickLayout;
}
