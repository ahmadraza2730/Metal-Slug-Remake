#pragma once
#include "Infantry.h"
#include "World.h"
#include "HandGrenadeProjectile.h"
class GrenadeSoldier :public Infantry
{
private:
	int throwCooldown;
public:
	GrenadeSoldier(float startX, float startY)
		:Infantry(startX, startY, 50, 80, 2, 1.5f, 10, 1, 3)
	{
		velX-=speed;
		facingRight=false;
		throwCooldown=120;
	}
    void update() override
    {
        applyGravity();

        if (isOnGround)
        {
            x += velX;

            if (throwCooldown > 0)
            {
                throwCooldown--;
            }
            else
            {
                throwCooldown = 150;
            }
        }
    }
    
    void enemyShoot(World* world, float playerX, float playerY)
    {
        if (throwCooldown > 0) return;
        throwCooldown = 150;

        facingRight = (playerX > x);
        velX = facingRight ? speed : -speed;

        HandGrenadeProjectile* g = new HandGrenadeProjectile(
            x + width / 2.0f,
            y + height / 2.0f,
            facingRight,
            NULL,
            NULL
        );
        world->spawnProjectile(g);
    }

    void draw(sf::RenderWindow& window, float camX) {
        sprite.setPosition(x-camX,y);

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

    ~GrenadeSoldier() {}
};