//
//  GameFramework.h
//  sfml_sample
//
//  Created by Giannandrea vicidomini on 02/03/2021.
//

#ifndef GameFramework_h
#define GameFramework_h
#include <SFML/Graphics.hpp>


class GameFramework
{

public:
    
    
    GameFramework(const int &width, const int &height, const std::string &title)
    :window(sf::VideoMode(width,height),title,sf::Style::Titlebar | sf::Style::Close)
    {
        this->width = width;
        this->height = height;
        this->window.setFramerateLimit(60);
        this->isPaused = false;
    }
    
    void run()
    {
        this->onCreate();
        
        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Time deltaTime = deltaClock.restart();
            sf::Event e;
            while (window.pollEvent(e))
            {
                
                if (e.type == sf::Event::Closed)
                {
                    window.close();
                }
                
                this->onEvent(e);
            }
            
            if(!isPaused){
                
                this->onUpdate(deltaTime);
                window.display();
            }
            //printf("%i \n",isPaused);
        }

    }

    virtual void onCreate() = 0;
        
    
    virtual void onUpdate(const sf::Time& deltaTime) = 0;
        
    
    virtual void onEvent(const sf::Event &event){}
        
    
private:
    
    sf::RenderWindow window;
    int width;
    int height;
    bool isPaused;
    friend class Demo;

    
};

#endif /* GameFramework_h */
