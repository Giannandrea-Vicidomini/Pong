#ifndef Particle_h
#define Particle_h
#include "GameObject.h"
#include <iostream>

class Particle : public GameObject
{
private:
    int lifetime;
public:
    
    Particle(const sf::Vector2f &pos,const sf::Texture& tx,const int& lifetime = 60);
    void update() override ;
    void applyForce(float x, float y);
    void draw(sf::RenderWindow& window) override;
    void applyForce(const sf::Vector2f &force);
    sf::Vector2f getSize()const override ;
    bool isDead();
    void kill();
    
};

bool Particle::isDead(){
    return lifetime<=0;
}

void Particle::applyForce(const sf::Vector2f &force)
{
    acceleration += force;
}

sf::Vector2f Particle::getSize() const
{
    return sf::Vector2f(obj.getTextureRect().width * obj.getScale().x, obj.getTextureRect().height * obj.getScale().y);
}

void Particle::applyForce(float x, float y)
{
    acceleration += sf::Vector2f(x, y);
}

Particle::Particle(const sf::Vector2f &pos,const sf::Texture& tx, const int& lifetime) : 
GameObject(pos),
lifetime(lifetime)
{
    texture = tx;
    obj.setTexture(texture);
    obj.setScale(0.26,0.26);
}

void Particle::update(){
    sf::Vector2f temp = velocity + acceleration;
    velocity.x = temp.x;
    velocity.y = temp.y;
    obj.setPosition(obj.getPosition() + velocity);
    acceleration.x = 0;
    acceleration.y = 0;
    lifetime = lifetime -1;
    
}

void Particle::draw(sf::RenderWindow& window){
    window.draw(obj);
}

void Particle::kill(){
    lifetime = 0;
}

#endif