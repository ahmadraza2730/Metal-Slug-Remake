#pragma once
#include "AquaticVehicle.h"

class EnemySub : public AquaticVehicle
{
private:
    bool  active;
    float rocketx;
    float rocketY;
    float rocketvelx;
    float rocketvely;
    bool  rocketfired;
    float fireCooldown;
    sf::Texture rocketTexture;
    sf::Sprite  rocketSprite;
public:
    EnemySub(float startX, float startY)
        : AquaticVehicle(startX, startY, 2.5f, 7)
    {
        active = true;
        rocketx = 0;
        rocketY = 0;
        rocketvelx = 0;
        rocketvely = 0;
        rocketfired = false;
        fireCooldown = 0;
    }
    void loadTexture(const char* subPath, const char* rocketPath)
    {
        texture.loadFromFile(subPath);
        rocketTexture.loadFromFile(rocketPath);
        sprite.setTexture(texture);
        rocketSprite.setTexture(rocketTexture);
    }
    void moveLeft()
    {
        speedx = -maxspeed;
    }
    void moveRight()
    {
        speedx = maxspeed;
    }
    void shoot()
    {
        if (fireCooldown > 0)
        {
            return;
        }
        rocketfired = true;
        rocketx = x;
        rocketY = y;
        rocketvelx = 7.0f;
        rocketvely = -8.0f; 
        fireCooldown = 150;    
    }
    void fireAtPlayer(float playerX, float playerY)
    {
        if (fireCooldown > 0) return;

        rocketfired = true;
        rocketx = x;
        rocketY = y;
        if (playerX > x)
        {
            rocketvelx = 7.0f;
        }
        else
        {
            rocketvelx = -7.0f;
        }

        rocketvely = -8.0f;
        fireCooldown = 150;
    }
    void update()
    {
        x += speedx;
        y += speedy;
        if (rocketfired)
        {
            rocketx += rocketvelx;
            rocketY += rocketvely;
            if (rocketY < 0 || rocketY > 900)
            {
                rocketfired = false;
            }
        }

        if (fireCooldown > 0)
        {
            fireCooldown--;
        }
    }
    void draw(sf::RenderWindow& window, float camX)
    {
        sprite.setPosition(x - camX, y);
        window.draw(sprite);
        if (rocketfired)
        {
            rocketSprite.setPosition(rocketx - camX, rocketY);
            window.draw(rocketSprite);
        }
    }
    bool  isActive() 
    { 
        return active; 
    }
    void  setActive(bool v) 
    { 
        active = v; 
    }
    bool  hasRocket() 
    { 
        return rocketfired; 
    }
    float getRocketX() 
    { 
        return rocketx; 
    }
    float getRocketY() 
    { 
        return rocketY; 
    }

    ~EnemySub() 
    { }
};