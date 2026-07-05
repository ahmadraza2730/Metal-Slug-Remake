#pragma once
#include "Player.h"
class Marco : public Player
{
private:
    int pistolAmmo;   
public:
    Marco(float startX, float startY)
        : Player(startX, startY, 50, 100, 100, 5.0f, 12.0f)
    {
        pistolAmmo = -1;  
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
            sprite.setScale(0.3f, 0.3f);
        else
            sprite.setScale(-0.3f, 0.3f);

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
    int getPistolAmmo() 
    { 
        return pistolAmmo; 
    }
    ~Marco() 
    { }
};