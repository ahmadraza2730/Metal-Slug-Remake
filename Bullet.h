#pragma once
#include "StraightProjectile.h"

class Bullet : public StraightProjectile
{
private:
    sf::RectangleShape shape;

public:
    Bullet(float startX, float startY, float vx, float vy, bool playerOwned, Player* shooter, Weapon* weapon)
        : StraightProjectile(startX, startY, vx, vy, 20, 1000.0f, playerOwned, false, shooter, weapon)
    {
        shape.setSize(sf::Vector2f(10.0f, 5.0f));
        if (playerOwned)
            shape.setFillColor(sf::Color::Yellow);
        else
            shape.setFillColor(sf::Color::Red);
    }

    Bullet(float startX, float startY, bool facingRight)
        : StraightProjectile(startX, startY,
            facingRight ? 15.0f : -15.0f, 0.0f,
            3, 1000.0f, true, false, NULL, NULL)
    {
        shape.setSize(sf::Vector2f(10.0f, 5.0f));
        shape.setFillColor(sf::Color::Yellow);
    }

    void draw(sf::RenderWindow& window, float camX) override
    {
        if (!active) return;
        shape.setPosition(x - camX, y);
        window.draw(shape);
    }

    sf::FloatRect getBounds() const override
    {
        return sf::FloatRect(x, y, 10.0f, 5.0f);
    }

    ~Bullet() {}
};