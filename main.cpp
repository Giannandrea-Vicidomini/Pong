#include "GameFramework.h"
#include <iostream>
#include "game_objects/Ball.h"
#include "game_objects/Paddle.h"
#include "utils/Random.h"
#include "game_objects/Ray.h"
#include "game_objects/Score.h"
#include "game_objects/ParticleSystem.h"
#include "game_objects/Particle.h"

class Demo : public GameFramework
{
public:
    sf::Texture tx;
    Ball ball;
    Paddle paddle;
    Random rng;
    Ray velRappr;
    sf::RectangleShape target;
    Score score;
    bool started = false;
    sf::Font font;
    sf::Text pressStart;
    sf::Text playAgain;
    bool isGameOver = false;

    Demo(const int &width, const int &height, const std::string &title)
        : GameFramework(width, height, title),
          ball(sf::Vector2f(window.getSize().x / 2-20, window.getSize().y / 2-100)),
          paddle(sf::Vector2f(window.getSize().x / 2, window.getSize().y - 60)),
          rng(),
          velRappr(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), ball.getVelocity()),
          score(window)
    {
        
    }

    void onEvent(const sf::Event &e) override
    {

        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::P)
        {

            if (isPaused == true)
            {
                isPaused = false;
            }
            else if (isPaused == false)
            {
                isPaused = true;
            }
        }

        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Space)
        {
            if(!started){
                int i = rng.randInt(0, 1);
                if (i == 0)
                {
                    ball.applyForce(sf::Vector2f(10, 10));
                }
                else
                {
                    ball.applyForce(sf::Vector2f(-10, 10));
                }
                started = true;
            }
        }
        
        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Space)
        {
            if(started && isGameOver){
            
                score.reset();
                isGameOver = false;
                started = false;
            }
        }

        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Q)
        {
            window.close();
        }

        
    }

    void onCreate() override
    {
        //setup
        
        
        //target.setFillColor(sf::Color(0,0,0));
        target.setPosition(sf::Vector2f(window.getSize().x / 2 - 100, -29.0f));
        target.setSize(sf::Vector2f(200, 50.0f));
        tx.loadFromFile("./resources/img/paddle.png");
        target.setTexture(&tx);
        

        if(!font.loadFromFile("./resources/fonts/prstart.ttf")){
            printf("Could not load font\n");
            exit(1);
        }
        
        pressStart.setFont(font);
        pressStart.setString("Press Spacebar");
        pressStart.setPosition(window.getSize().x/2-350, window.getSize().y/2-50);
        pressStart.setCharacterSize(50);

        playAgain.setFont(font);
        playAgain.setPosition(window.getSize().x/2-350, window.getSize().y/2-50);
        playAgain.setCharacterSize(50);

        started = false;
        isGameOver = false;

    }

    void onUpdate(const sf::Time &deltaTime) override
    {
        gameLogic(deltaTime);
    }

private:
    void gameLogic(const sf::Time &deltaTime){
        
        if(!started){
            
            homeScreen();
        }
        else if(isGameOver){
            
            gameOver();
        }
        else{
            game(deltaTime);
        }
    }

    void game(const sf::Time &deltaTime){
        window.clear(sf::Color(0, 0, 0));

        score.draw(window);
        window.draw(target);
        ball.update();
        
        if (ball.checkBoundaries(window, target, score) == 3)
        {
            playAgain.setString("Your score: " + std::to_string(score.getScore()));
            score.saveScore();
            isGameOver = true;
            ball.reset();
        }

        paddle.draw(window);
        paddle.checkBoundaries(window);
        paddle.update(window);
        ball.onCollision(paddle);
        ball.draw(window);
        
    }

    void homeScreen(){
        window.clear(sf::Color::Black);
        window.draw(pressStart);
    }

    void gameOver(){
        window.clear(sf::Color::Black);
        window.draw(playAgain);
    }
};

int main(void)
{

    Demo demo(1200, 1080, "Pong");
    demo.run();
    return 0;
}
