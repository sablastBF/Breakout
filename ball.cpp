#include "ball.hpp"
#include "glm/gtc/matrix_transform.hpp"

Ball::Ball(float radius, string &text, shared_ptr<Renderer> r): GameObject(glm::vec2(2.0f*radius), text, r){
    this -> radius = radius;
}

// dodavanje novih lopta, namjenjeno je za vise lopta
Ball::Ball(shared_ptr<Ball> b, glm::vec2 velocity){
    this -> radius = b -> radius/1.2f;
    this -> render = b -> render;
    this -> pos =  b -> pos;
    this -> siz = b -> siz/1.2f;
    this -> velocty = velocity;
    this -> textureID = b -> textureID;
    this -> stuck = false;
}

void Ball::updatePos(float dt){
    if (this -> stuck) return ;
    glm::vec2 newPos = this -> pos + this -> velocty * dt;
    if (newPos.x < 0.0f || newPos.x + this -> radius*2.0f > this -> render -> getWidth()){
        this -> velocty.x = -this -> velocty.x ;
    }     

    if (newPos.y < 0.0f || newPos.y + this -> radius*2.0f > this -> render -> getHeight()){
        this -> velocty.y = -this -> velocty.y;
        
    }       
    newPos = glm::clamp(newPos, glm::vec2(0.0f), glm::vec2( this -> render -> getWidth() - 2.0f*this -> radius,  this -> render -> getHeight()- 2.0f*this -> radius));

    this -> pos = newPos;
    this -> path.push_back(this -> pos.x + this -> radius);
    this -> path.push_back(this -> pos.y + this -> radius);
}

void Ball::drawLinePath(){  
   // if (path.size() < 1000) return ;
    cout << path.size() << endl;
    this -> lineShader = Shader("shaders/lineShader.vs", "shaders/lineShader.fs");
    this -> lineShader.use();
    
    glGenVertexArrays(1, &this -> lineVAO);
    glBindVertexArray(this -> lineVAO);

    glGenBuffers(1, &this -> lineVBO);

    glBindBuffer(GL_ARRAY_BUFFER, this -> lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(path)*sizeof(float)*100, path.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    this -> lineShader.use();
    this -> lineShader.setMat4("projection", this -> render -> getProjection());
    
    for (int i = 0; i < path.size() ;i+=2){
        cout << i<<" " <<this -> path[i]<<" "<< path[i + 1]<<endl;
    }

    glBindVertexArray(this -> lineVAO);
    glDrawArrays(GL_LINE_STRIP, 0, this -> path.size()/2);
    glBindVertexArray(0);
}


float Ball::getRadius(){return this -> radius;}

void Ball::changeVelocity(){
    this -> velocty.x = -this -> velocty.x ;
    this -> velocty.y = -this -> velocty.y ;
}

void Ball::changeVelocityY(){
    this -> velocty.y = -this -> velocty.y ;
}
void Ball::changeVelocityX(){
    this -> velocty.x = -this -> velocty.x ;
}
glm::vec2 Ball::getVelocrty(){return this ->velocty;}

void Ball::setVelocrty(glm::vec2 velocty){this ->velocty = velocty;}


void Ball::flipStuck(){ this -> stuck = false;}
bool Ball::getStuck(){return this -> stuck;}

