#ifndef BallSfx_h
#define BallSfx_h
#include <SFML/Audio.hpp>

class BallSfx
{
private:
    sf::SoundBuffer b_boing;
    sf::Sound sBoing;
    sf::SoundBuffer b_ricochet;
    sf::Sound sRicochet;
    sf::SoundBuffer b_thud;
    sf::Sound sThud;
    sf::SoundBuffer b_go;
    sf::Sound sGo;
    sf::SoundBuffer b_cling;
    sf::Sound sCLing;

public:

    void boing();
    void speed();
    void thud();
    void go();
    void cling();
    bool isGoPlaying();
    BallSfx(/* args */);

};

BallSfx::BallSfx(/* args */)
{
    if (!b_boing.loadFromFile("./resources/sounds/Boing.wav"))
    {
        printf("Couldn't load boing file\n");
        exit(EXIT_FAILURE);
    }

    sBoing.setBuffer(this->b_boing);

    if (!b_go.loadFromFile("./resources/sounds/Byeball.wav"))
    {
        printf("Couldn't load byeball file\n");
        exit(EXIT_FAILURE);
    }

    sGo.setBuffer(b_go);

    if (!b_ricochet.loadFromFile("./resources/sounds/Ricochet.wav"))
    {
        printf("Couldn't load ricochet file\n");
        exit(EXIT_FAILURE);
    }

    sRicochet.setBuffer(b_ricochet);

    if (!b_thud.loadFromFile("./resources/sounds/wall.wav"))
    {
        printf("Couldn't load thud file\n");
        exit(EXIT_FAILURE);
    }

    sThud.setBuffer(b_thud);

    if (!b_cling.loadFromFile("./resources/sounds/Wowpulse.wav"))
    {
        printf("Couldn't load cling file\n");
        exit(EXIT_FAILURE);
    }

    sCLing.setBuffer(b_cling);
}

void BallSfx::boing(){
    sBoing.play();
    
}

void BallSfx::speed(){
    sRicochet.play();
}

void BallSfx::thud(){
    sThud.play();
}

void BallSfx::go(){
    sGo.play();
}

void BallSfx::cling(){
    sCLing.play();
}

bool BallSfx::isGoPlaying(){
    return sGo.getStatus() == 2;
}



#endif