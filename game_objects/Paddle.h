#ifndef Paddle_h
#define Paddle_h
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>

class Paddle : public GameObject
{
private:
    /* data */
public:
    Paddle(const sf::Vector2f &pos);
    int checkBoundaries(const sf::RenderWindow &window);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getSize() const;
    void update(const sf::RenderWindow& window);
    
};

Paddle::Paddle(const sf::Vector2f &pos)
    : GameObject(pos)
{
    texture.loadFromFile("./resources/img/paddle.png");
    obj.setTexture(texture);
    obj.setScale(1.20f,0.8);
    obj.setColor(sf::Color(255,255,255));
}

int Paddle::checkBoundaries(const sf::RenderWindow &window)
{

    sf::Vector2u size = window.getSize();
    int width = size.x;
    int height = size.y;
    float sWidth = getSize().x;
    float sHeight = getSize().y;

    if (obj.getPosition().x + sWidth >= width)
    { //Collides right wall
        obj.setPosition(width - sWidth, obj.getPosition().y);
        
        return 1;
    }

    if (obj.getPosition().x <= 0)
    { //Collides left wall
        obj.setPosition(0, obj.getPosition().y);
        
        return 2;
    }

    return 0;
}

void Paddle::draw(sf::RenderWindow& window){
    window.draw(obj);
}

sf::Vector2f Paddle::getSize()const{
    return sf::Vector2f(obj.getTextureRect().width*obj.getScale().x,obj.getTextureRect().height*obj.getScale().y);
}

void Paddle::update(const sf::RenderWindow& window){
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    sf::Vector2u wSize = window.getSize();
   
    if(pos.x>=0 && pos.x <=wSize.x && pos.y>=0 && pos.y<=wSize.y){
        obj.setPosition(pos.x-getSize().x/2,obj.getPosition().y);
    }
    
}



#endif