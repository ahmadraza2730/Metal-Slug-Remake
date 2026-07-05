#pragma once
#include "Player.h"

class Eri : public Player
{
public:
    Eri(float startX, float startY)
        : Player(startX, startY, 50, 80, 90, 5.5f, 13.0f)
    {
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

    ~Eri() {}
};