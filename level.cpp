#include <stb_image.h>
#include <vector>
#include <memory>

#include "string"

#include "level.hpp"
# define PI  3.14159265358979323846f


using namespace tinyxml2;

void Level::draw(){
    this -> background -> draw();
    this -> paddle -> draw();
    for (shared_ptr<Brick> brick: this -> levelBrickLayout) brick -> draw();

    for (shared_ptr<Ball> ball: this -> balls) {
        ball -> draw();
        ball -> drawLinePath();
    }
}

void Level::loadLevelFromFile(string path){

    unsigned int n = 20, m = 20;
    unsigned int spacC = 20, rowC = 20;

    string pathBackground;
    XMLDocument levelXml;
    levelXml.LoadFile(path.c_str());

    XMLElement * levelData = levelXml.FirstChild()->ToElement();

    string paddleTexture;
    if (levelData->FindAttribute("PaddleTexture")){
        paddleTexture = levelData->FindAttribute("PaddleTexture")->Value();
    } else {
        paddleTexture = "textures/paddle/paddle.png";
        cout <<"Background texture not found set to default."<<endl;
    }

    glm::vec2 paddleSize = glm::vec2(100.0f, 15.0f);
    this -> paddle = shared_ptr<Paddle>(new Paddle(paddleSize, paddleTexture, this  -> render));
    

    string ballTexture;
    if (levelData->FindAttribute("BallTexture")){
        ballTexture = levelData->FindAttribute("BallTexture")->Value();
    } else {
        ballTexture = "textures/ball/ball.png";
        cout <<"Background texture not found set to default."<<endl;
    }
    this -> balls.push_back(shared_ptr<Ball>(new Ball(10.0f, ballTexture, this -> render)));
    this -> setBallPositionStuck();

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
    this -> background = shared_ptr<GameObject>(new GameObject(glm::vec2(0.0f), glm::vec2(this -> render -> getWidth(), this -> render -> getHeight() ),pathBackground, this -> render));

    float width_ =  static_cast<float>(this -> render -> getWidth())/ static_cast<float>(n);
    float height_ = static_cast<float>(this -> render -> getHeight()) / (static_cast<float>(m));
    double minSquare = min(width_, height_);
    minSquare = minSquare;

// dodajemo vrste brkova
    XMLElement *brickS = levelData -> FirstChildElement("BrickTypes");
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
    int offset = this -> render -> getWidth() - minSquare*n;
    offset/=2;
    for (double i = 0; i < m; i++){
        for (double j = 0; j < n; j++){
           if (this -> brick.find(v[k]) == this -> brick.end()) {k++;continue;}
           shared_ptr<Brick> br = shared_ptr<Brick>(new Brick(this -> brick[v[k++]]));
           br -> setPos(glm::vec2( minSquare * j , minSquare * i ));
           br -> setSiz(glm::vec2(minSquare -rowC ,minSquare - spacC));
           this -> levelBrickLayout.push_back(br);
        }
    } 
}

void Level::setBallPositionStuck(){
    glm::vec2 newPos = paddle -> getPos();
    newPos.x += paddle -> getSiz().x/2.0f - balls[0] -> getRadius();
    newPos.y += -  balls[0] -> getRadius()*2.0f;
    balls[0] -> setPos(newPos);
}

void Level::addBrick( XMLElement* brick){

    string id = brick->FindAttribute("Id")->Value();
    string texturePath = brick->FindAttribute("Texture")->Value();
    unsigned int hitPoints;
    shared_ptr<Brick> brk = shared_ptr<Brick>(new Brick(texturePath, this -> render));
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

    unsigned int numberOfBalls;
    if (brick->FindAttribute("AddBalls")){
        brick->FindAttribute("AddBalls")->QueryUnsignedValue(&numberOfBalls);
    } else {
        numberOfBalls = 0;
        //cout <<"BreakScore not specified set to default path."<<endl;
    }

    brk -> setHit(hitPoints);
    brk -> setBreakScore(breakScore);
    brk -> setBreakSound(soundPathBreak);
    brk -> setHitSound(soundPathHit);
    brk -> setNumberOfBalls(numberOfBalls);
    this -> brick[id] = brk;
}

Level::Level(string path,shared_ptr<Renderer> rendere){
    this -> render = rendere;
    this -> loadLevelFromFile(path);
}

vector<shared_ptr<Brick> > & Level::getBricks(){
    return this -> levelBrickLayout;
}

vector<shared_ptr<Ball> > & Level::getBalls(){
    return this -> balls;
}


void Level::addBalls(shared_ptr<Ball> ball,unsigned int N){
    cout <<N<<endl;
    double normaX = 0.0, normaY = 0.0;
    double fi = 0.0;
    for (double i = 0; i < N; i++){
        fi = i/N*2.0*PI;
        normaX = cos(fi);
        normaY = sin(fi);

        glm::vec2 newVelocty = glm::vec2(cos(fi), sin(fi));
        glm::vec2 v =(newVelocty * glm::length(ball -> getVelocrty()));
        shared_ptr<Ball> b = shared_ptr<Ball>(new Ball(ball, v));
        this -> balls.push_back(b);
    }
    // ball -> textureID;
    // shared_ptr<Ball> b =  shared_ptr(new Ball(ball -> textureID));
}

