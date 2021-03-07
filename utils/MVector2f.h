#ifndef MVector2f_h
#define MVector2f_h
#include <SFML/Graphics.hpp>

class MVector2f : public sf::Vector2f
{
private:
    /* data */
    
public:
    MVector2f(const float& x,const float& y):sf::Vector2f(x,y)
    {

    }
    MVector2f operator *(const int& factor){
        return MVector2f(this->x*factor,this->y*factor);
    }

    MVector2f operator +(const MVector2f& other) {
        return MVector2f(this->x+other.x,this->y*other.y);
        printf("DIOCANE\n");
    }

};



#endif