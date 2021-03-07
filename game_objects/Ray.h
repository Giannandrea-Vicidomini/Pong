#ifndef Ray_h
#define Ray_h
#include <SFML/Graphics.hpp>

class Ray
{
private:
    sf::Vector2f origin;
    const sf::Vector2f& direction;

    sf::VertexArray getLine();
public:
    void draw(sf::RenderWindow& window);
    Ray(const sf::Vector2f& origin, const sf::Vector2f& direction);
    
};

Ray::Ray(const sf::Vector2f& origin, const sf::Vector2f& direction)
: origin(origin),
direction(direction)
{
}

sf::VertexArray Ray::getLine(){
    sf:: Vector2f head = origin + sf::Vector2f(direction.x*6,direction.y*6);
    sf::Vertex v1(origin);
    v1.color = sf::Color(255,0,0);
    sf::Vertex v2(head);
    v2.color = sf::Color(255,0,0);
    sf::VertexArray vao(sf::Lines);
    vao.append(v1);
    vao.append(v2);
    return vao;
}


void Ray::draw(sf::RenderWindow& window){
    window.draw(getLine());
}

#endif