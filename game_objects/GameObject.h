//
//  GameObject.h
//  sfml_sample
//
//  Created by Giannandrea vicidomini on 03/03/2021.
//

#ifndef GameObject_h
#define GameObject_h
#include <SFML/Graphics.hpp>
#include <string>
#include "../utils/MVector2f.h"

class GameObject
{
private:
    /* data */
    //sf::Vector2f velocity;
    MVector2f velocity;
    sf::Vector2f acceleration;
    sf::Texture texture;
    sf::Sprite obj;

    friend class Ball;
    friend class Paddle;
    friend class Particle;
    friend class ParticleSystem;

public:

    const sf::Sprite& getSprite() const;
    GameObject(const sf::Vector2f pos);
    virtual void update() {}
    virtual int checkBoundaries(const sf::RenderWindow& window) {return 0;}
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::Vector2f getSize()const = 0;
    virtual void onCollision(const GameObject& other) {};
    
};

const sf::Sprite& GameObject::getSprite() const{
    return obj;
}

GameObject::GameObject(const sf::Vector2f pos): obj(),velocity(0,0)
{
    obj.setPosition(pos);
}




#endif /* GameObject_h */
