#pragma once
#include "Undead.h"

class Zombie : public Undead
{
private:
    int shootCooldown;
    bool transformsPlayer;  

public:
    Zombie(float startX, float startY)
        : Undead(startX, startY, 50, 80, 5, 0.4f, 100)
    {
        shootCooldown = 120;
        transformsPlayer = true;
        velX = -speed;
        facingRight = false;
    }

    void loadTexture(const char* path)
    {
        texture.loadFromFile(path);
        sprite.setTexture(texture);
    }

    void update() override
    {
        applyGravity();

        if (isOnGround)
        {
            x += velX;

            if (shootCooldown > 0)
                shootCooldown--;
            else
                shootCooldown = 120;
        }
    }

    void enemyShoot(World* world, float playerX, float playerY)
    {
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

    void draw(sf::RenderWindow& window, float camX) override
    {
        sprite.setPosition(x - camX, y);

        if (facingRight)
            sprite.setScale(0.3f, 0.3f);
        else
            sprite.setScale(-0.3f, 0.3f);

        window.draw(sprite);
    }

    bool canTransform() 
    { 
        return transformsPlayer; 
    }

    ~Zombie() {}
};