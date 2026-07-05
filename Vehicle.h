#pragma once
#include <SFML/Graphics.hpp>
#include "DamageState.h"

class VehicleRider; 

class Vehicle
{
protected:
    float x;
    float y;
    float speedx;
    float speedy;
    float maxspeed;
    int health;
    bool isAlive;
    bool occupied;
    int damageState;
    float stateTimer;
    sf::Texture texture;
    sf::Sprite sprite;
    VehicleRider* rider; 

public:
    Vehicle(float startX, float startY, float spd, int hp)
    {
        x = startX;
        y = startY;
        speedx = 0;
        speedy = 0;
        maxspeed = spd;
        health = hp;
        isAlive = true;
        occupied = false;
        damageState = STATE_NORMAL;
        stateTimer = 0;
        rider = NULL;
    }

    bool loadTexture(const char* path)
    {
        if (texture.loadFromFile(path))
        {
            sprite.setTexture(texture);
            return true;
        }
        return false;
    }

    void enter(VehicleRider* newRider)
    {
        occupied = true;
        rider = newRider;
    }

    void exit()
    {
        occupied = false;
        rider = NULL;
        speedx = 0;
        speedy = 0;
    }

    void syncRiderPosition();

    void takeDamage(int damage)
    {
        if (damageState == STATE_NORMAL)
        {
            damageState = STATE_INJURED;
            stateTimer = 60;
        }
        else if (damageState == STATE_INJURED)
        {
            damageState = STATE_CRITICAL;
            stateTimer = 60;
        }
        else if (damageState == STATE_CRITICAL)
        {
            damageState = STATE_DEAD;
            isAlive = false;
        }
    }

    void updateDamageState()
    {
        if (stateTimer > 0)
        {
            stateTimer--;
            if (stateTimer <= 0)
            {
                if (damageState == STATE_INJURED || damageState == STATE_CRITICAL)
                {
                    damageState = STATE_NORMAL;
                }
            }
        }
    }

    float getX() const
    {
        return x;
    }
    float getY() const
    {
        return y;
    }
    int getHealth() const
    {
        return health;
    }
    bool getIsAlive() const
    {
        return isAlive;
    }
    bool isOccupied() const
    {
        return occupied;
    }
    int getDamageState()
    {
        return damageState;
    }
    VehicleRider* getRider()
    {
        return rider;
    }
    float getWidth() const
    {
        return sprite.getGlobalBounds().width;
    }
    float getHeight() const
    {
        return sprite.getGlobalBounds().height;
    }
    void setX(float newX)
    {
        x = newX;
    }
    void setY(float newY)
    {
        y = newY;
    }

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window, float camX) = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void shoot() = 0;
    virtual void landOnGround(float groundY) {}

    virtual ~Vehicle() {}
};