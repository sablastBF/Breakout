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

    if (levelData->FindAttribute("RowCount")){
        levelData->FindAttribute("RowCount")->QueryUnsignedValue(&m);
    } else {
        m = 20;
        cout <<"RowCount Not Found set to default value."<<endl;
    }

    if (levelData->FindAttribute("ColumnCount")){
        levelData->FindAttribute("ColumnCount")->QueryUnsignedValue(&n);
    } else {
        n = 20;
        cout <<"ColumnCount Not Found set to default value."<<endl;
    }


    if (levelData->FindAttribute("RowSpacing")){
        levelData->FindAttribute("RowSpacing")->QueryUnsignedValue(&rowC);
    } else {
        rowC = 0;
        cout <<"RowSpacing Not Found set to default value."<<endl;
    }

    if (levelData->FindAttribute("ColumnSpacing")){
        levelData->FindAttribute("ColumnSpacing")->QueryUnsignedValue(&spacC);
    } else {
        spacC = 0;
        cout <<"ColumnSpacing Not Found set to default value."<<endl;
    }

    if (levelData->FindAttribute("BackgroundTexture")){
        pathBackground = levelData->FindAttribute("BackgroundTexture")->Value();
    } else {
        pathBackground = "textures/background/background.jpg";  
        cout <<"Background texture not found set to default."<<endl;
    }
    this -> background = new GameObject(glm::vec2(0.0f), glm::vec2(this -> rendere -> getWidth(), this -> rendere -> getHeight() ),pathBackground, this -> rendere);

    float width_ =  static_cast<float>(this -> rendere -> getWidth())/ static_cast<float>(n);
    float height_ = static_cast<float>(2.0f/3.0f*this -> rendere -> getHeight()) / (static_cast<float>(m));
    float minSquare = min(width_, height_);
    minSquare = minSquare;

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
    int offset = this -> rendere -> getWidth() - minSquare*n;
    offset/=2;
    cout << offset << endl;
    for (float i = 0; i < m; i++){
        for (float j = 0; j < n; j++){
           if (this -> brick.find(v[k]) == this -> brick.end()) {k++;continue;}
           Brick *br = new Brick(this -> brick[v[k++]]);
           br -> setPos(glm::vec2( width_ * j + rowC, height_ * i + spacC));
           br -> setSiz(glm::vec2(width_-  rowC, height_ - spacC));
           this -> levelBrickLayout.push_back(br);
        }
    } 
}

void Level::addBrick( XMLElement * brick){

    string id = brick->FindAttribute("Id")->Value();
    string texturePath = brick->FindAttribute("Texture")->Value();
    unsigned int hitPoints;
    Brick *brk = new Brick(texturePath, this -> rendere);
    if (brick->FindAttribute("HitPoints")  == nullptr || string(brick->FindAttribute("HitPoints")->Value()) == string("Infinite") ){
        brk -> setUndestrojable(true);
    } else {
        brick->FindAttribute("HitPoints")->QueryUnsignedValue(&hitPoints);
    }  
    
    string soundPathBreak;
    if (brick->FindAttribute("BreakSound")){
        soundPathBreak = brick->FindAttribute("BreakSound")->Value();
    } else {
        soundPathBreak ="audio/bricks/Heart.wav"; // ovo treba promjenit na neki papir
       // cout <<"BreakSound not specified, set to default path."<<endl;
    }

    string soundPathHit;
    if (brick->FindAttribute("HitSound")){
        soundPathHit = brick->FindAttribute("HitSound")->Value();
    } else {
        soundPathHit ="audio/bricks/Heart.wav"; // ovo treba promjenit na neki papir
        cout <<"HitSound not specified, set to default path."<<endl;
    }


    unsigned int breakScore;
    if (brick->FindAttribute("BreakScore")){
        brick->FindAttribute("BreakScore")->QueryUnsignedValue(&breakScore);
    } else {
        breakScore = 0;
        //cout <<"BreakScore not specified set to default path."<<endl;
    }

    brk -> setHit(hitPoints);
    brk -> setBreakScore(breakScore);
    brk -> setBreakSound(soundPathBreak);
    brk -> setHitSound(soundPathHit);

    this -> brick[id] = brk;
}

Level::Level(string path,Renderer *rendere){
    this -> rendere = rendere;
    this -> loadLevelFromFile(path);
}

vector<Brick *> &  Level::getBricks(){
    return this -> levelBrickLayout;
}
