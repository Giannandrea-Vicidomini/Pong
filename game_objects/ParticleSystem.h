#ifndef ParticleSystem_h
#define ParticleSystem_h
#include "Particle.h"
#include "../utils/MVector2f.h"
#include <vector>
#include "../utils/Random.h"
#include <cmath>

class ParticleSystem: public GameObject
{
private:
    Random rng;
    sf::Vector2f gravity;
    std::vector<std::shared_ptr<Particle> > particles;
    void generateParticles(const int& num);
public:
    void reset();
    ParticleSystem();
    ParticleSystem(const sf::Vector2f &pos);
    sf::Vector2f getSize()const override{return sf::Vector2f(0.0f,0.0f);};
    void draw(sf::RenderWindow& window)override;
    void update()override;
    void emit();
    void setPosition(const sf::Vector2f& newPos);
    void db();
    ~ParticleSystem();
    
};

ParticleSystem::ParticleSystem():
GameObject(sf::Vector2f(50,50)),
gravity(0,0.8)
{
    if(!texture.loadFromFile("./resources/img/particle.png")){
        printf("could not load particle texture\n");
        exit(EXIT_FAILURE);
    }
}

ParticleSystem::ParticleSystem(const sf::Vector2f &pos):
GameObject(pos),
gravity(0.0f,0.8)
{
}

void ParticleSystem::draw(sf::RenderWindow& window){
    for(int i=0; i<particles.size(); i++){
        particles[i]->draw(window);
    }
}

void ParticleSystem::update(){
    
    for(int i=0; i<particles.size(); i++){
        std::shared_ptr<Particle> p = particles[i];
        //printf("%f,%i\n",p.velocity.x,p.getLife());
        if(p->isDead()){
            
            particles.erase(particles.begin()+i);
            i--;
        }
        else{
            p->applyForce(gravity);
            //printf("gravity: %f\n",gravity.y);
            p->update();
        }
    }   
}
void ParticleSystem::emit(){
    int toCreate = rng.randInt(10,20);
    generateParticles(toCreate);

}

void ParticleSystem::generateParticles(const int& num){
    for(int i=0; i<num; i++){
        int life = rng.randInt(10,75);
        int mag = rng.randInt(5,28);
        int angle = rng.randInt(0,360);
        MVector2f direction(cos(angle*M_PI/180.0f),sin(angle*M_PI/180.0f));
        direction = direction*mag;
        
        std::shared_ptr<Particle> p(new Particle(sf::Vector2f(obj.getPosition()),texture,life));
        p->applyForce(direction);
        particles.push_back(p);

        
    }
}

void ParticleSystem::setPosition(const sf::Vector2f& newPos){
    obj.setPosition(newPos);
}

ParticleSystem::~ParticleSystem(){
    
}

void ParticleSystem::reset(){
    for(int i=0; i<particles.size(); i++){
        particles[i]->kill();
    }
}

#endif