#pragma once
#include "Alien.h"

class Martian : public Alien
{
private:
    // phase 1 — pod
    float podX;
    float podY;
    float beamCooldown;
    bool  podAlive;

    sf::Texture podTexture;
    sf::Sprite  podSprite;

    // phase 2 — on foot
    int shootCooldown;

public:
    Martian(float startX, float startY)
        : Alien(startX, startY, 50, 80, 3, 1.0f, 10)
    {
        podX = startX;
        podY = startY - 100;  // pod starts above
        beamCooldown = 90;
        podAlive = true;
        shootCooldown = 90;
        phase = 1;
        velX = -speed;
        facingRight = false;
    }

    void loadTexture(const char* footPath, const char* podPath)
    {
        texture.loadFromFile(footPath);
        sprite.setTexture(texture);
        podTexture.loadFromFile(podPath);
        podSprite.setTexture(podTexture);
    }

    void takeDamage(int dmg) override
    {
        if (phase == 1)
        {
            // damage goes to pod
            health -= dmg;
            if (health <= 0)
            {
                // pod explodes — switch to phase 2
                podAlive = false;
                phase = 2;
                health = 3;    // reset HP for phase 2
                x = podX;
                y = podY;
            }
        }
        else
        {
            // phase 2 — normal damage
            health -= dmg;
            if (health <= 0)
            {
                health = 0;
                isAlive = false;
            }
        }
    }
    void enemyShoot(World* world, float playerX, float playerY)
    {
        if (phase != 2) return;   // early exit if not phase 2
        if (shootCooldown > 0) return;
        shootCooldown = 120;

        facingRight = (playerX > x);
        velX = facingRight ? speed : -speed;
        float bulletX = x + width / 2.0f;
        float bulletY = y + height / 2.0f;
        float bulletVX = facingRight ? 6.0f : -6.0f;

        Bullet* b = new Bullet(bulletX, bulletY, bulletVX, 0.0f, false, NULL, NULL);
        world->spawnProjectile(b);
    }

    void update() override
    {
        if (phase == 1)
        {
            podX += velX;

            if (beamCooldown > 0)
                beamCooldown--;
            else
                beamCooldown = 90;  
        }
        else
        {
            applyGravity();

            if (isOnGround)
            {
                x += velX;

                if (shootCooldown > 0)
                    shootCooldown--;
                else
                    shootCooldown = 90;
            }
        }
    }

    void draw(sf::RenderWindow& window, float camX) override
    {
        if (phase == 1)
        {
            podSprite.setPosition(podX - camX, podY);
            window.draw(podSprite);
        }
        else
        {
            sprite.setPosition(x - camX, y);

            if (facingRight)
                sprite.setScale(0.3f, 0.3f);
            else
                sprite.setScale(-0.3f, 0.3f);

            window.draw(sprite);
        }
    }

    int   getCurrentPhase() { return phase; }
    float getPodX() { return podX; }
    float getPodY() { return podY; }
    bool  isPodAlive() { return podAlive; }

    ~Martian() {}
};