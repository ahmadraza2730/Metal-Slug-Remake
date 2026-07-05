#pragma once
#include "StraightProjectile.h"

class LaserProjectile : public StraightProjectile
{
private:
    sf::RectangleShape shape;
    float duration;
    bool facingRight;
    float beamWidth;

public:
    LaserProjectile(float startX, float startY, bool fr, Player* shooter, Weapon* weapon)
        : StraightProjectile(startX, startY, 0.0f, 0.0f, 999, 99999.0f, true, false, shooter, weapon)
    {
        duration = 60.0f;
        beamWidth = 1600.0f;
        facingRight = fr;

        shape.setSize(sf::Vector2f(beamWidth, 6.0f));
        shape.setFillColor(sf::Color(0, 255, 255, 220));
    }

    void update() override
    {
        if (!active) return;
        duration--;
        if (duration <= 0)
        {
            active = false;
        }
    }

    void draw(sf::RenderWindow& window, float camX) override
    {
        if (!active) return;

        if (facingRight)
            shape.setPosition(x - camX, y);
        else
            shape.setPosition(x - camX - beamWidth, y);

        window.draw(shape);
    }

    sf::FloatRect getBounds() const override
    {
        return sf::FloatRect(x, y, 1600.0f, 6.0f);
    }

    ~LaserProjectile() {}
};