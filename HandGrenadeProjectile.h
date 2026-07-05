#pragma once
#include "BallisticProjectile.h"

class HandGrenadeProjectile : public BallisticProjectile
{
private:
    sf::CircleShape grenadeShape;
    sf::CircleShape explosionShape;
    bool exploded;
    float explosionTimer;
    float blastRadius;

public:
    HandGrenadeProjectile(float startX, float startY, bool facingRight, Player* shooter, Weapon* weapon)
        : BallisticProjectile(startX, startY, (facingRight ? 6.0f : -6.0f), -10.0f, 20, true, true, shooter, weapon)
    {
        exploded = false;
        explosionTimer = 30.0f;
        blastRadius = 100.0f;

        grenadeShape.setRadius(6.0f);
        grenadeShape.setFillColor(sf::Color::Green);

        explosionShape.setRadius(blastRadius);
        explosionShape.setFillColor(sf::Color(255, 165, 0, 128));
        explosionShape.setOrigin(blastRadius, blastRadius);
    }

    void onHitGround() override
    {
        exploded = true;

    }

    void update() override
    {
        if (!active) return;

        if (!exploded)
        {
            BallisticProjectile::update();
        }
        else
        {
            explosionTimer--;
            if (explosionTimer <= 0)
            {
                active = false;
            }
        }
    }

    void draw(sf::RenderWindow& window, float camX) override
    {
        if (!active) return;

        if (!exploded)
        {
            grenadeShape.setPosition(x - camX, y);
            window.draw(grenadeShape);
        }
        else
        {
            explosionShape.setPosition(x - camX, y);
            window.draw(explosionShape);
        }
    }

    sf::FloatRect getBounds() const override
    {
        return sf::FloatRect(x - blastRadius, y - blastRadius, blastRadius * 2, blastRadius * 2);
    }

    float getBlastRadius()
    {
        return blastRadius;
    }

    bool isExploded()
    {
        return exploded;
    }

    ~HandGrenadeProjectile() {}
};