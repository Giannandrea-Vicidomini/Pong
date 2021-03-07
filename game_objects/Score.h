#ifndef Score_h
#define Score_h
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <json/json.h>
#include <fstream>


class Score
{
private:
    int hiScore;
    int points;
    sf::Font font;
    sf::Text hiScoreTxt;
    sf::Text current;
    void loadScore();
    const char* path = "./resources/scores.json"; 
    /* data */
public:
    Score( sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void updateScore(const int& amt);
    void saveScore();
    void reset();
    const int getScore() const ;
    ~Score();
};

const int Score::getScore()const{
    return points;
    printf("%i\n",points);
}

void Score::reset(){
    points = 0;
    loadScore();
}

Score::Score(sf::RenderWindow& window)
{
    loadScore();
    int scoreSize = 100;
    float x = window.getSize().x;
    float y = window.getSize().y;
    
    points = 0;
    

    if(!font.loadFromFile("./resources/fonts/prstart.ttf")){
        printf("font could not be loaded\n");
        exit(EXIT_FAILURE);
    }
    hiScoreTxt.setFont(font);
    hiScoreTxt.setFillColor(sf::Color::White);
    hiScoreTxt.setPosition(sf::Vector2f(x - x*0.25,5));
    hiScoreTxt.setCharacterSize(25);

    current.setFont(font);
    current.setFillColor(sf::Color::White);
    current.setPosition(sf::Vector2f(x/2-scoreSize/2,y/2-scoreSize/2));
    current.setCharacterSize(scoreSize);
}

void Score::draw(sf::RenderWindow& window){
    std::string str("HiScore: ");
    str.append(std::to_string(hiScore));

    hiScoreTxt.setString(str);
    window.draw(hiScoreTxt);

    current.setString(std::to_string(points));
    window.draw(current);
}

void Score::updateScore(const int& amt){
    points += amt;
}

void Score::saveScore(){
    if(points>hiScore){
        Json::Value root;
        std::ifstream file(path);
        file>>root;
        root["high_score"] = std::to_string(points);
        file.close();
        std::ofstream outFile(path);
        outFile << root;
        outFile.close();
    }
}

void Score::loadScore(){
    Json::Value root;
    std::ifstream file(path);
    file>>root;

    hiScore = std::stoi(root["high_score" ].asString());
}

Score::~Score()
{
}


#endif