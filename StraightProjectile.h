#pragma once
#include "Projectile.h"

class StraightProjectile : public Projectile
{
protected:
    float maxRange;

public:
    StraightProjectile(float startX, float startY, float vx, float vy, int dmg, float range, bool playerOwned, bool isExplosive, Player* shooter, Weapon* weapon)
        : Projectile(startX, startY, vx, vy, 0.0f, dmg, playerOwned, isExplosive, shooter, weapon)
    {
        maxRange = range;
    }

    void update() override
    {
        x += velX;
        y += velY;

        float dx = x - spawnX;
        float dy = y - spawnY;
        float distanceTravelled = sqrt(dx * dx + dy * dy);

        if (distanceTravelled > maxRange)
        {
            active = false;
        }
    }

    virtual void draw(sf::RenderWindow& window, float camX) = 0;
    virtual sf::FloatRect getBounds() const = 0;

    virtual ~StraightProjectile() {}
};