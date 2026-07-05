#pragma once
#include "Infantry.h"
#include "World.h"
#include "RocketProjectile.h"

class BazookaSoldier : public Infantry
{
private:
    int shootCooldown;

public:
    BazookaSoldier(float startX, float startY)
        : Infantry(startX, startY, 50, 80, 2, 1.0f, 10, 1, 2)
    {
        velX = -speed;
        facingRight = false;
        shootCooldown = 180;
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
                shootCooldown = 180;
            }
        }
    }


    void enemyShoot(World* world, float playerX, float playerY)
    {
        if (shootCooldown > 0) return;
        shootCooldown = 180;

        facingRight = (playerX > x);
        velX = facingRight ? speed : -speed;

        float vx = facingRight ? 5.0f : -5.0f;

        RocketProjectile* r = new RocketProjectile(
            x + width / 2.0f,
            y + height / 2.0f,
            vx, 0.0f,
            false, NULL, NULL
        );
        world->spawnProjectile(r);
    }

    void draw(sf::RenderWindow& window, float camX) override
    {
        sprite.setPosition(x - camX, y);

        if (facingRight)
            sprite.setScale(0.3f, 0.3f);
        else
            sprite.setScale(-0.3f, 0.3f);

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

    ~BazookaSoldier() {}
};