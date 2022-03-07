//#include <memory>
#include "game.hpp"
using namespace irrklang;
extern Game *brakeOut; /* Declaration of the variable */


void procesInput( GLFWwindow *window, int key, int scancode, int action, int mods );


Game::Game(unsigned int width_, unsigned int height_){
    this -> width = width_;
    this -> height = height_;
}

void Game::addLevel(string pathToLevel){
    levels.push_back(pathToLevel);
    numberOfLevels++;
}

GameState Game::getGameState(){return this -> gameState;}
void Game::setGameState(GameState v){this -> gameState = v;}

// game manager, pokrece iduce levele, resetira levele...
void Game::RunGame(){
    // radi sve stvari koje su potrebne za sve levele
    window = crateWindow( this -> width, this -> height);
    SoundEngine = createIrrKlangDevice();
    TextRender = shared_ptr<textRender>(new textRender("fonts/AmaticSC-Regular.ttf" ,this -> width, this -> height));

    if (!window) return ;
    this  -> render = shared_ptr<Renderer>(new Renderer( this -> width, this -> height,"shaders/basic_brick.vs","shaders/basic_brick.fs" ));

    curetLevel = 0;
    glfwSetKeyCallback(window, procesInput);


    while(!glfwWindowShouldClose(window)){
        if (gameState == STARTSCREEN){
            this -> RunStartScreen();
        }

        if (gameState == RUNLEVEL){ 
            this -> RunLevel(levels[curetLevel++]);   

            if (gameState == RUNLEVEL && curetLevel == numberOfLevels) gameState = ENDSCREEN;
        }

        if (gameState == GAMEOVERSCREEN){ 
            this -> RunGameOverScreen();   
        }

        if (gameState == ENDSCREEN){ 
            this -> RunEndScreen();   
        }
    }

}

void Game::RunLevel(string levelPath){
    this -> level = shared_ptr<Level>(new Level(levelPath,  this -> render));

    float lastFrame = 0.0f;
    float currentFrame = 0.0f;
    SoundEngine->play2D("audio/background/UA.mp3", true);

    string sc;
    string numberOfBalls, numberOfBrick, lives;
    string levelNumber, numberOfDistroid;

    drawGameInfoFlag = 1;

    while(gameState == RUNLEVEL && !glfwWindowShouldClose(window)){
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;        
        procesInputForPaddle(this -> window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
     

        this -> updatePos(deltaTime);
        this -> draw();
        if (this -> level -> isGameWon()){
            this -> gameScore += gameScoreCurrent;
            gameScoreCurrent= 0;
            this -> gameScore += (level -> getTezina()*1000.0f - currentFrame) + (level -> getNumberOfBalls() - 1) * 100;
            this -> level -> setBallPositionStuck();
            return ;
        }
        if (this -> level -> doesGameHaveBall()){
            gameScoreCurrent = 0;
            this -> level -> reste();
            this -> level -> decreseLive();
            if (this -> level -> getNumberOFLives() == 0) gameState = GAMEOVERSCREEN;
        }

        sc = to_string(this -> gameScore + gameScoreCurrent);
        numberOfBalls = to_string(this -> level -> getNumberOfBalls());
        numberOfBrick = to_string(this -> level -> getNumberOfBricks());
        numberOfDistroid = to_string(this -> level -> getNumberOfDistroid());
        levelNumber = to_string(curetLevel + 1);
        lives = to_string(this->level -> getNumberOFLives());
        float k = 0.0f;
        float of = 5.0f;
        this -> TextRender ->  RenderText( "Score: "+sc, 5.0f, of+60.0f * (k++), 1.0f, glm::vec3(1.0f));
        this -> TextRender ->  RenderText( "Level: "+levelNumber, 5.0f,   of+60.0f * (k++), 1.0f, glm::vec3(1.0f));
        this -> TextRender ->  RenderText( "Balls: "+numberOfBalls, 5.0f,   of+60.0f * (k++), 1.0f, glm::vec3(1.0f));

        this -> TextRender ->  RenderText( numberOfDistroid +" / " +  numberOfBrick  , 5.0f,   of+60.0f * (k++), 1.0f, glm::vec3(1.0f)); 
        this -> TextRender ->  RenderText( "Brick: ", 5.0f,   of+60.0f * (k++), 1.0f, glm::vec3(1.0f)); 
        this -> TextRender ->  RenderText( "Lives: "+lives, 5.0f,   this -> render -> getHeight() - 60.0f, 1.0f, glm::vec3(1.0f));

        if (drawGameInfoFlag){
            drawGameInfo();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }   
}

void Game::drawGameInfo(){
    int k = 3;
    this -> TextRender ->  RenderText( "Press Space to play" , this -> render -> getWidth() /2.0f, this -> render -> getHeight() - 60.0f*(k++), 1.0f, glm::vec3(1.0f));
    this -> TextRender ->  RenderText( "LEFT & RIGHT ARROW TO MOVE " , this -> render -> getWidth() /2.0f, this -> render -> getHeight()  - 60.0f*(k++), 1.0f, glm::vec3(1.0f));
    this -> TextRender ->  RenderText( "R TO RESET " , this -> render -> getWidth() /2.0f, this -> render -> getHeight()  - 60.0f*(k++), 1.0f, glm::vec3(1.0f));
    this -> TextRender ->  RenderText( "ESC TO QUIT " , this -> render -> getWidth() /2.0f, this -> render -> getHeight()  - 60.0f*(k++), 1.0f, glm::vec3(1.0f));
}

void Game::draw(){
    this -> level -> draw();
}

GLFWwindow*  Game::crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return nullptr;
    }    

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{   
    glViewport(0, 0, width, height);
}

//STARTSCREEN
void Game::RunStartScreen(){

    SoundEngine->play2D("audio/background/UA.mp3", true);

    while(gameState == STARTSCREEN && !glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        int k = 1;
        this -> TextRender ->  RenderText( "BRAKEOUT BY BARBA", 5.0f, 60.0f, 1.5f, glm::vec3(1.0f));
        this -> TextRender ->  RenderText( "Press Space to play" , 5.0f, this -> render -> getHeight() - 60.0f*(k++), 1.0f, glm::vec3(1.0f));
        this -> TextRender ->  RenderText( "ESC TO QUIT " , 5.0f, this -> render -> getHeight()  - 60.0f*(k++), 0.5f, glm::vec3(1.0f));
        glfwSwapBuffers(window);
        glfwPollEvents();   
    }
}

void Game::RunEndScreen(){
    SoundEngine->play2D("audio/background/UA.mp3", true);
    while(gameState == ENDSCREEN && !glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        this -> TextRender ->  RenderText( "WICTORY", 5.0f, 60.0f, 1.0f, glm::vec3(1.0f));
        glfwSwapBuffers(window);
        glfwPollEvents();   
    }
}

void Game::RunGameOverScreen(){

    SoundEngine->play2D("audio/background/UA.mp3", true);
    while(gameState == GAMEOVERSCREEN && !glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        this -> TextRender ->  RenderText( "GameOVER", 5.0f, 60.0f, 1.0f, glm::vec3(1.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();   
    }
}

bool Game::CheckCollision(shared_ptr<GameObject> one, shared_ptr<GameObject> two) // AABB - AABB collision
{   
    bool collisionX = one -> getPos().x + one -> getSiz().x > two ->getPos().x &&
        two -> getPos().x + two -> getSiz().x > one -> getPos().x;

    bool collisionY = one -> getPos().y + one -> getSiz().y > two ->getPos().y &&
        two -> getPos().y + two -> getSiz().y > one -> getPos().y;
    return collisionX && collisionY;
}


void  Game::updatePos(float dt){
    shared_ptr<Paddle> paddle = this -> level -> getPaddle();
    vector<shared_ptr<Brick>> &brks = this -> level -> getBricks();
    vector<shared_ptr<Ball>> &balls = this -> level -> getBalls();
    int siz = balls.size();
    shared_ptr<Ball> b = nullptr;
    for (int i = 0; i < siz; i++){
        b = balls[i];
        if (b -> updatePos(dt)){
            this -> level -> distorjBall();
            if (!this -> level -> doesGameHaveBall())
            balls.erase(balls.begin() + i);
            i--;siz--;
            continue;
        } 
        
         if (this -> CheckCollision(b, paddle)){
            // uzmemo pozicju lopte, pozicju paddla 
            //ball -> changeVelocityY();

            glm::vec2 bp = b -> getPos() + b -> getRadius();
            glm::vec2 pad = paddle -> getPos() + paddle -> getSiz()/2.0f;
            glm::vec2 newVelocty = bp - pad;
            newVelocty.y -= paddle -> getSiz().x*2.0f;
            newVelocty  = normalize(newVelocty);
            b -> setVelocrty(newVelocty * glm::length(b -> getVelocrty()));
        }

        // izmedu lopte i brikova

        for (int i =  brks.size() - 1; ~i; i--){
            if (brks[i] -> getDestroid()) continue;

            if (this -> CheckCollision(b, brks[i])){
                if (brks[i] -> getUndestrojable() == false && brks[i] -> chechHit() ){
                
                    this -> gameScoreCurrent += brks[i] -> getBreakScore();
                    brks[i] -> setDistroid();
                    level -> distorjBrick();
                    brks[i] -> playBreakSound(SoundEngine);
                    level -> addBalls(b, brks[i] -> getNumberOfBalls());
                } else {
                    brks[i] -> playHitSound(SoundEngine);
                }
                break;
            }
        }
    }
}

// ovo tude treba ispraviti 
bool Game::CheckCollision(shared_ptr<Ball> ball, shared_ptr<GameObject> two) 
{

    glm::vec2 center(ball -> getPos() + ball -> getRadius());
    glm::vec2 aabb_half_extents(two -> getSiz().x  / 2.0f,two -> getSiz().y / 2.0f);
    glm::vec2 aabb_center(
        two -> getPos().x + aabb_half_extents.x, 
        two-> getPos().y + aabb_half_extents.y);

    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;
    if (glm::length(difference) > ball -> getRadius()) return false;


    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(difference), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }

    if (best_match == 1 || best_match == 3){
        ball->changeVelocityX(); // reverse horizontal velocity
        // relocate
        float penetration = ball->getRadius() - std::abs(difference.x);
        glm::vec2 pos = ball -> getPos();
        if (best_match == 3)
            pos.x += penetration;  
        else
            pos.x -= penetration; 
        ball -> setPos(pos);
    } else {
        ball->changeVelocityY(); // reverse horizontal velocity
        // relocate
        float penetration = ball->getRadius() - std::abs(difference.y);
        glm::vec2 pos = ball -> getPos();
        if (best_match == 2)
            pos.y += penetration;  
        else
            pos.y -= penetration; 
        ball -> setPos(pos);
    }


    return true;
} 

void Game::procesInputForPaddle( GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        
    if (this -> gameState == RUNLEVEL){
        shared_ptr<Paddle> paddle = level -> getPaddle();
        shared_ptr<Ball> ball = level -> getBall();int state = glfwGetKey(window, GLFW_KEY_E);

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            paddle -> updatePos(glm::vec2(-1.0f,0.0f), deltaTime);
            if (ball -> getStuck()){
                level -> setBallPositionStuck();
            }
            this -> drawGameInfoFlag = 0;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            paddle -> updatePos(glm::vec2(1.0f,0.0f), deltaTime);
            if (ball -> getStuck()){
                level -> setBallPositionStuck();
            }
            this -> drawGameInfoFlag = 0;
        }
    }
}

void procesInput( GLFWwindow *window, int key, int scancode, int action, int mods ){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (brakeOut -> getGameState() == STARTSCREEN){
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
            brakeOut->setGameState(RUNLEVEL);
            brakeOut -> setdrawGameInfoFlag(0);
        }

    } else if (brakeOut -> getGameState() == RUNLEVEL){
        shared_ptr<Ball> ball =  brakeOut -> getLevel() -> getBall();
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
            ball -> setUnStuck();
            brakeOut -> setdrawGameInfoFlag(0);
        }
        // reset
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            brakeOut -> setgameScoreCurrent(0);
            brakeOut -> getLevel() -> reste();
        }
    } else if (brakeOut -> getGameState() == ENDSCREEN){
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            brakeOut->setGameState(STARTSCREEN);
            brakeOut->setcuretLevel(0);
            brakeOut->setgameScoreCurrent(0);
            brakeOut->setgameScore(0);

        }
     } else if (brakeOut -> getGameState() == GAMEOVERSCREEN){
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            brakeOut->setGameState(STARTSCREEN);
            brakeOut->setcuretLevel(0);
            brakeOut->setgameScoreCurrent(0);
            brakeOut->setgameScore(0);
        }
    }
}

