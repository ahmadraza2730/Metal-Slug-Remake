#pragma once
#include "GroundVehicle.h"

class Bradley : public GroundVehicle
{
private:
    bool  active;
    float missilex;
    float missiley;
    float missilevelx;
    float missilevely;
    float missileGravity;
    bool  missileFired;
    float fireCooldown;
    sf::Texture missileTexture;
    sf::Sprite  missileSprite;
public:
    Bradley(float startX, float startY)
        : GroundVehicle(startX, startY, 2.0f, 7)  
    {
        active = true;
        missilex = 0;
        missiley = 0;
        missilevelx = 0;
        missilevely = 0;
        missileGravity = 0.3f;
        missileFired = false;
        fireCooldown = 0;
    }
    void loadTexture(const char* vehiclePath, const char* missilePath)
    {
        texture.loadFromFile(vehiclePath);
        missileTexture.loadFromFile(missilePath);
        sprite.setTexture(texture);
        missileSprite.setTexture(missileTexture);
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

        missileFired = true;
        missilex = x;
        missiley = y;
        missilevelx = 8.0f;   
        missilevely = -10.0f; 
        fireCooldown = 180;    
    }
    void approachPlayer(float playerX)
    {
        if (x < playerX)
            moveRight();
        else if (x > playerX)
            moveLeft();
        else
            speedx = 0;
    }
    void update()
    {
        x += speedx;
        y += speedy;
        applyGravity();
        if (missileFired)
        {
            missilevely += missileGravity;
            missilex += missilevelx;
            missiley += missilevely;
            if (missiley > 900)
            {
                missileFired = false;
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
        if (missileFired)
        {
            missileSprite.setPosition(missilex - camX, missiley);
            window.draw(missileSprite);
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
    bool  hasMissile() 
    { 
        return missileFired; 
    }
    float getMissileX() 
    { 
        return missilex; 
    }
    float getMissileY() 
    { 
        return missiley; 
    }

    ~Bradley() 
    { }
};