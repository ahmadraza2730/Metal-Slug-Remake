#pragma once
#include "BallisticProjectile.h"

class FireBombProjectile : public BallisticProjectile
{
private:
    sf::CircleShape grenadeShape;
    sf::CircleShape explosionShape;
    sf::CircleShape firePoolShape;
    bool exploded;
    float explosionTimer;
    float firePoolTimer;
    float blastRadius;
    float firePoolRadius;
    bool firePoolActive;

public:
    FireBombProjectile(float startX, float startY, bool facingRight, Player* shooter, Weapon* weapon)
        : BallisticProjectile(startX, startY, facingRight ? 6.0f : -6.0f, -10.0f, 20, true, true, shooter, weapon)
    {
        exploded = false;
        explosionTimer = 30.0f;
        firePoolTimer = 600.0f;
        blastRadius = 100.0f;
        firePoolRadius = 192.0f;
        firePoolActive = false;

        grenadeShape.setRadius(6.0f);
        grenadeShape.setFillColor(sf::Color(255, 100, 0));

        explosionShape.setRadius(blastRadius);
        explosionShape.setFillColor(sf::Color(255, 165, 0, 128));
        explosionShape.setOrigin(blastRadius, blastRadius);

        firePoolShape.setRadius(firePoolRadius);
        firePoolShape.setFillColor(sf::Color(255, 50, 0, 150));
        firePoolShape.setOrigin(firePoolRadius, firePoolRadius);
    }

    void onHitGround() override
    {
        exploded = true;
        firePoolActive = true;

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
            if (explosionTimer > 0)
            {
                explosionTimer--;
            }

            if (firePoolActive)
            {
                firePoolTimer--;
                if (firePoolTimer <= 0)
                {
                    firePoolActive = false;
                    active = false;
                }
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
            if (explosionTimer > 0)
            {
                explosionShape.setPosition(x - camX, y);
                window.draw(explosionShape);
            }

            if (firePoolActive)
            {
                firePoolShape.setPosition(x - camX, y);
                window.draw(firePoolShape);
            }
        }
    }

    sf::FloatRect getBounds() const override
    {
        return sf::FloatRect(x - firePoolRadius, y - firePoolRadius, firePoolRadius * 2, firePoolRadius * 2);
    }

    float getFirePoolRadius()
    {
        return firePoolRadius;
    }

    bool isExploded()
    {
        return exploded;
    }

    bool isFirePoolActive()
    {
        return firePoolActive;
    }

    ~FireBombProjectile() {}
};