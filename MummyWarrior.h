#pragma once
#include "Undead.h"

class MummyWarrior : public Undead
{
private:
    float resTimer;       
    bool immuneToBullets;

public:
    MummyWarrior(float startX, float startY)
        : Undead(startX, startY, 50, 80, 5, 0.5f, 100)
    {
        resTimer = 0;
        immuneToBullets = true;
        velX = -speed;
        facingRight = false;
    }

    void loadTexture(const char* path)
    {
        texture.loadFromFile(path);
        sprite.setTexture(texture);
    }

    void takeDamage(int dmg) override
    {
        if (!crumbled)
        {
            crumbled = true;
            crumbleTimer = 180;  
        }
    }

    void takeFireDamage(int dmg)
    {
        health -= dmg;
        if (health <= 0)
        {
            health = 0;
            isAlive = false;
        }
    }

    void update() override
    {
        if (crumbled)
        {
           
            crumbleTimer--;
            if (crumbleTimer <= 0)
            {
                crumbled = false;
                health = 5;    
            }
            return;
        }

        applyGravity();
        x += velX;
    }

    void draw(sf::RenderWindow& window, float camX) override
    {
        if (crumbled) return;  
        sprite.setPosition(x - camX, y);

        if (facingRight)
            sprite.setScale(0.3f, 0.3f);
        else
            sprite.setScale(-0.3f, 0.3f);

        window.draw(sprite);
    }

    bool isCrumbledNow() { return crumbled; }

    ~MummyWarrior() {}
};