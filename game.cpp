//#include <memory>
#include "game.hpp"

using namespace irrklang;

Game::Game(unsigned int width_, unsigned int height_){

    this -> width = width_;
    this -> height = height_;
    //this -> projection = glm::ortho(0.0f, static_cast<float>( this -> width), static_cast<float>(this -> height), 0.0f, -1.0f, 1.0f);  
  
    GLFWwindow* window = crateWindow( this -> width, this -> height);
    if (!window) return ;
    this  -> render = shared_ptr<Renderer>(new Renderer( this -> width, this -> height,"shaders/basic_brick.vs","shaders/basic_brick.fs" ));
    this  -> brickRender = shared_ptr<Renderer>(new Renderer( this -> width, this -> height,"shaders/basic_brick.vs","shaders/basic_brick.fs" ));

    // string path = "ball.png";
    // Brick *br = new Brick(glm::vec2(20.0f), glm::vec2(100.0f), path, this -> render);
    string levelPath = "levels/dragon.xml";
    this -> level = shared_ptr<Level>(new Level(levelPath,  this -> render));

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    SoundEngine = createIrrKlangDevice();
    SoundEngine->play2D("audio/background/UA.mp3", true);

    while(!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
     
        processInput(window, deltaTime);

        this -> updatePos(deltaTime);
        this -> draw();
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }   
}


void Game::processInput(GLFWwindow *window, float deltaTime)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    shared_ptr<Paddle> paddle = this -> level -> getPaddle();
    shared_ptr<Ball> ball = this -> level -> getBall();

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        paddle -> updatePos(glm::vec2(-1.0f,0.0f),deltaTime);
        if (ball -> getStuck()){
            this -> level -> setBallPositionStuck();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        paddle -> updatePos(glm::vec2(1.0f,0.0f),deltaTime);
        if (ball -> getStuck()){
            this -> level -> setBallPositionStuck();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        ball -> flipStuck();
    }
}

void Game::draw(){
    this -> level -> draw();
}

GLFWwindow*  Game::crateWindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Moj Lomljenje Van", NULL, NULL);
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

    for (shared_ptr<Ball> b: balls){ 
        b -> updatePos(dt);
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
                
                    this -> gameScore += brks[i] -> getBreakScore();
                    brks[i] -> setDistroid();
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

