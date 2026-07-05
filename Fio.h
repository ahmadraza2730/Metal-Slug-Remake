#pragma once
#include "Player.h"

class Fio : public Player
{
private:
    int heavyAmmo;

public:
    Fio(float startX, float startY)
        : Player(startX, startY, 50, 80, 110, 4.8f, 12.5f)
    {
        heavyAmmo = 150;
    }

    void update() override
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

    int getHeavyAmmo()
    {
        return heavyAmmo;
    }

    ~Fio() {}
};
