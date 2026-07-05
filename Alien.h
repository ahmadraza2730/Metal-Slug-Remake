#pragma once
#include "Enemy.h"

class Alien : public Enemy
{
protected:
    int   phase;          
    float phaseTimer;     

public:
    Alien(float startX, float startY, int w, int h, int hp, float s, int d)
        : Enemy(startX, startY, w, h, hp, s, d)
    {
        phase = 1;
        phaseTimer = 0;
    }

    int getPhase() 
    { 
        return phase; 
    }

    virtual void update() override = 0;
    virtual void draw(sf::RenderWindow& window, float camX) override = 0;

    virtual ~Alien() {}
};