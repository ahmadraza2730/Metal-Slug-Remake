#pragma once
#include "Projectile.h"

class FlameProjectile : public Projectile
{
private:
    sf::RectangleShape shape;
    float duration;
    float maxDuration;
    float range;

public:
    FlameProjectile(float startX, float startY, bool playerOwned, Player* shooter, Weapon* weapon)
        : Projectile(startX, startY, 0.0f, 0.0f, 0.0f, 2, playerOwned, false, shooter, weapon)
    {
        fireType = true;
        range = 320.0f;
        maxDuration = 240.0f;
        duration = maxDuration;
        shape.setSize(sf::Vector2f(range, 40.0f));
        shape.setFillColor(sf::Color(255, 100, 0, 180));
    }

    void update() override;
    void draw(sf::RenderWindow& window, float camX) override;
    sf::FloatRect getBounds() const override;

    ~FlameProjectile() {}
};