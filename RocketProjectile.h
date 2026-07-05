#pragma once
#include "StraightProjectile.h"

class RocketProjectile : public StraightProjectile
{
private:
    sf::RectangleShape shape;

public:
    RocketProjectile(float startX, float startY, float vx, float vy, bool playerOwned, Player* shooter, Weapon* weapon)
        : StraightProjectile(startX, startY, vx, vy, 50, 1000.0f, playerOwned, true, shooter, weapon)
    {
        shape.setSize(sf::Vector2f(20.0f, 10.0f));
        shape.setFillColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow& window, float camX) override
    {
        if (!active) return;
        shape.setPosition(x - camX, y);
        window.draw(shape);
    }

    sf::FloatRect getBounds() const override
    {
        return sf::FloatRect(x, y, 20.0f, 10.0f);
    }

    ~RocketProjectile() {}
};