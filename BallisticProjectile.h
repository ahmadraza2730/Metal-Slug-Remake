#pragma once
#include "Projectile.h"

class BallisticProjectile : public Projectile
{
protected:
    float groundY;

public:
    BallisticProjectile(float startX, float startY, float vx, float vy, int dmg, bool playerOwned, bool isExplosive, Player* shooter, Weapon* weapon)
        : Projectile(startX, startY, vx, vy, 0.4f, dmg, playerOwned, isExplosive, shooter, weapon)
    {
        groundY = 9999.0f;
    }

    void setGroundY(float gy)
    {
        groundY = gy;
    }

    void update() override
    {
        if (!active) return;

        velY += gravity;
        x += velX;
        y += velY;

        if (y >= groundY)
        {
            y = groundY;
            onHitGround();
        }
    }

    virtual void onHitGround() = 0;

    virtual void draw(sf::RenderWindow& window, float camX) = 0;
    virtual sf::FloatRect getBounds() const = 0;

    virtual ~BallisticProjectile() {}
};