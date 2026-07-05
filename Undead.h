#pragma once
#include "Enemy.h"

class Undead : public Enemy
{
protected:
    bool crumbled;        
    float crumbleTimer;   

public:
    Undead(float startX, float startY, int w, int h, int hp, float s, int d)
        : Enemy(startX, startY, w, h, hp, s, d)
    {
        crumbled = false;
        crumbleTimer = 0;
    }

    bool isCrumbled() 
    { 
        return crumbled; 
    }

    virtual void update() override = 0;
    virtual void draw(sf::RenderWindow& window, float camX) override = 0;

    virtual ~Undead() 
    { }
};