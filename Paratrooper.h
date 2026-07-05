#pragma once
#include "Infantry.h"

class Paratrooper : public Infantry
{
private:
    bool  landed;
    float descentSpeed;
    bool  parachuteOpen;
    int   shootCooldown;
    sf::Texture parachuteTexture;
    sf::Sprite  parachuteSprite;

public:
    Paratrooper(float startX, float startY)
        : Infantry(startX, startY, 50, 80, 2, 1.0f, 10, 2, 4)
    {
        shootCooldown = 120;
        landed = false;
        descentSpeed = 2.0f;
        parachuteOpen = true;
        velX = -speed;
        facingRight = false;
    }

    void loadTexture(const char* soldierPath, const char* parachutePath)
    {
        texture.loadFromFile(soldierPath);
        sprite.setTexture(texture);
        parachuteTexture.loadFromFile(parachutePath);
        parachuteSprite.setTexture(parachuteTexture);
    }

    void update() override
    {
        if (!landed)
        {
            y += descentSpeed;
            if (isOnGround)
            {
                landed = true;
                parachuteOpen = false;
                velY = 0;
            }
        }
        else
        {
            applyGravity();
            x += velX;
        }
    }

    void landOnGround(float groundY)
    {
        if (y + height >= groundY)
        {
            y = groundY - height;
            velY = 0;
            isOnGround = true;
            if (!landed)
            {
                landed = true;
                parachuteOpen = false;
            }
        }
        else
        {
            if (landed)
                isOnGround = false;
        }
    }

    void enemyShoot(World* world, float playerX, float playerY)
    {
        if (shootCooldown > 0) { shootCooldown--; return; }
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
        if (parachuteOpen)
        {
            parachuteSprite.setPosition(x - camX, y - 60);
            window.draw(parachuteSprite);
        }
        sprite.setPosition(x - camX, y);
        if (facingRight)
            sprite.setScale(1.0f, 1.0f);
        else
            sprite.setScale(-1.0f, 1.0f);
        window.draw(sprite);
    }

    bool hasLanded() { return landed; }

    ~Paratrooper() {}
};