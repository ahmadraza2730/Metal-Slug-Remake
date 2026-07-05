#pragma once
#include "Player.h"
class Tarma : public Player
{
private:
    bool hasMotorbike; 
public:
    Tarma(float startX, float startY)
        : Player(startX, startY, 50, 80, 130, 4.0f, 11.0f)
    {
        hasMotorbike = false;
    }
    void update()
    {
        applyGravity();
        if (shootCooldown > 0) shootCooldown--;
        if (grenadeCooldown > 0) grenadeCooldown--;
    }
void draw(sf::RenderWindow& window, float camX) override
{
    sprite.setPosition(x - camX, y);

    if (facingright)
        sprite.setScale(0.2f, 0.2f);
    else
        sprite.setScale(-0.2f, 0.2f);

    window.draw(sprite);
    
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
    bool getHasMotorbike() 
    { 
        return hasMotorbike; 
    }
    void setMotorbike(bool val) 
    { 
        hasMotorbike = val; 
    }
    ~Tarma() 
    { }
};