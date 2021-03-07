#ifndef Ball_h
#define Ball_h
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <math.h>
#include "BallSfx.h"
#include "Score.h"
#include "../utils/MVector2f.h"
#include "ParticleSystem.h"

class Ball : public GameObject
{
private:
    bool hard = false;
    ParticleSystem pSystem;
    BallSfx sfx;
    sf::Vector2f resetPos;
    sf::Vector2f computeBallDirection(const GameObject &other);
    /* data */
public:
    Ball(const sf::Vector2f &pos);
    void update()
    {

        sf::Vector2f temp = velocity + acceleration;
        velocity.x = temp.x;
        velocity.y = temp.y;
        obj.setPosition(obj.getPosition() + velocity);
        acceleration.x = 0;
        acceleration.y = 0;
        pSystem.update();
    }

    void draw(sf::RenderWindow &window)
    {
        
        window.draw(obj);
        pSystem.draw(window);
    }

    void applyForce(float x, float y)
    {
        acceleration += sf::Vector2f(x, y);
    }
    void applyForce(const sf::Vector2f &force)
    {
        acceleration += force;
    }

    int checkBoundaries(const sf::RenderWindow &window, const sf::RectangleShape &tgt, Score &score)
    {
        if(score.getScore()>=15 && hard == false){
            normaliseVelocity();
            velocity.x*=60;
            velocity.y*=60;
            hard = true;
        }

        sf::Vector2u size = window.getSize();
        int width = size.x;
        int height = size.y;
        float sWidth = getSize().x;
        float sHeight = getSize().y;

        if (obj.getPosition().x + sWidth >= width)
        { //Collides right wall
            obj.setPosition(width - sWidth, obj.getPosition().y);
            velocity.x *= -1;

            sfx.thud();
            return 1;
        }

        if (obj.getPosition().x <= 0)
        { //Collides left wall
            obj.setPosition(0, obj.getPosition().y);
            velocity.x *= -1;
            sfx.thud();
            return 2;
        }

        if (obj.getPosition().y + sHeight >= height)
        { //Collides bottom wall
            obj.setPosition(obj.getPosition().x, height - sHeight);
            velocity.y *= -1;
            sfx.go();
            //unsigned int t = 1000000;
            //usleep(t*1.12);

            while (sfx.isGoPlaying())
            {
                //do nothing
            }
            return 3;
        }
        if (obj.getPosition().y <= 0)
        { //Collides top wall
            obj.setPosition(obj.getPosition().x, 0);
            velocity.y *= -1;
            if (obj.getGlobalBounds().intersects(tgt.getGlobalBounds()))
            {
                sfx.cling();
                score.updateScore(1);
            }
            else
            {
                sfx.thud();
            }

            return 4;
        }
        return 0;
    }

    sf::Vector2f getSize() const
    {
        return sf::Vector2f(obj.getTextureRect().width * obj.getScale().x, obj.getTextureRect().height * obj.getScale().y);
    }

    void onCollision(const GameObject &other);
    sf::Vector2f &getVelocity();

    float getVMagnitude()
    {
        return sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
    }

    sf::Vector2f getSpriteCenter()
    {
        sf::Vector2f size = getSize();
        return sf::Vector2f(obj.getPosition().x + size.x / 2, obj.getPosition().y + size.y / 2);
    }

    void normaliseVelocity()
    {
        float mag = getVMagnitude();
        velocity.x/=mag;
        velocity.y/=mag;
    }

    void reset(){
        hard = false;
        pSystem.reset();
        obj.setPosition(resetPos);
        velocity.x=0;
        velocity.y=0;
        acceleration.x=0;
        acceleration.y=0;
    }
};


sf::Vector2f &Ball::getVelocity()
{
    return velocity;
}

Ball::Ball(const sf::Vector2f &pos)
    : GameObject(pos)
{
    resetPos = pos;
    texture.loadFromFile("./resources/img/ball.png");
    obj.setTexture(texture);
    obj.setScale(0.29, 0.29);
}

void Ball::onCollision(const GameObject &other)
{
    const sf::Sprite s1 = other.getSprite();

    bool collision = obj.getGlobalBounds().intersects(s1.getGlobalBounds());

    if (collision)
    {
        sf::Vector2f center = getSpriteCenter();
        sf::Vector2f paddlePos = other.getSprite().getPosition();
        float yoff = other.getSize().y;
        float xoff = other.getSize().x;

        if (center.y >= paddlePos.y && center.y <= paddlePos.y + yoff && !(center.x >= paddlePos.x && center.x <= paddlePos.x + xoff))
        {
            velocity.x *= -1;
        }
        else
        {
            
            sf::Vector2f newDir = computeBallDirection(other);
            float currentMag = getVMagnitude();
            velocity.x = newDir.x;
            velocity.y = newDir.y;
            normaliseVelocity();
            velocity.x*=currentMag;
            velocity.y*=currentMag;
            velocity.y *= -1;
        }
        /*
        if (center.x >= paddlePos.x && center.x <= paddlePos.x + xoff)
        {
            
            
        }

        */
        if (getVMagnitude() <= 40)
        {
            int factor = 4;
            float mod = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
            sf::Vector2f force((velocity.x / mod) * factor, (velocity.y / mod) * factor);
            applyForce(force);
            //printf("velocity: mag(%f)\n",sqrt(pow(velocity.x,2) + pow(velocity.y,2) ));
        }

        if (getVMagnitude() >= 29)
        {
            pSystem.setPosition(obj.getPosition());
            pSystem.emit();
            sfx.speed();
        }
        else
        {
            sfx.boing();
        }
    }
}

sf::Vector2f Ball::computeBallDirection(const GameObject &other)
{
    MVector2f left(-1,0.6);
    MVector2f right(1,0.6);
    sf::Vector2f center = getSpriteCenter();
    sf::Vector2f paddlePos = other.getSprite().getPosition();
    float yoff = other.getSize().y;
    float xoff = other.getSize().x;

    float scalar = (center.x - paddlePos.x)/xoff;

    
    sf::Vector2f res =(1-scalar)*left + (scalar)*right;
    return res;
}

#endif