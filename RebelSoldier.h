#pragma once
#include "Infantry.h"
#include "World.h"
#include "Bullet.h"

class RebelSoldier : public Infantry
{
private:
    int shootCooldown;

public:
    RebelSoldier(float startX, float startY)
        : Infantry(startX, startY, 50, 80, 2, 1.0f, 10, 2, 4)
    {
        velX = -speed;
        facingRight = false;
        shootCooldown = 60;
    }

    void update() override
    {
        applyGravity();

        if (isOnGround)
        {
            x += velX;

            if (shootCooldown > 0)
            {
                shootCooldown--;
            }
            else
            {
                shootCooldown = 120;
            }
        }
    }

    void enemyShoot(World* world, float playerX, float playerY)
    {
        if (shootCooldown > 0) return;
        shootCooldown = 120;

        // face the player
        facingRight = (playerX > x);
        velX = facingRight ? speed : -speed;

        float bulletX = x + width / 2.0f;
        float bulletY = y + height / 2.0f;
        float bulletVX = facingRight ? 6.0f : -6.0f;

        Bullet* b = new Bullet(bulletX, bulletY, bulletVX, 0.0f, false, NULL, NULL);
        world->spawnProjectile(b);
    }

    void draw(sf::RenderWindow& window, float camX) override
    {
        sprite.setPosition(x - camX, y);

        if (facingRight)
            sprite.setScale(1.0f, 1.0f);
        else
            sprite.setScale(-1.0f, 1.0f);

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

    ~RebelSoldier() {}
};