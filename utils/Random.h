#ifndef Random_h
#define Random_h
#include <random>

class Random
{
private:
    std::random_device rd;
    std::mt19937 gen;
public:
    Random();
    int randInt(const int& min,const int& max);
};

Random::Random():
    gen(rd())
{
}

int Random::randInt(const int& min, const int& max){
    std::uniform_int_distribution<> distr(min,max);
    return distr(gen);
}


#endif