#pragma once
#include "Infantry.h"

class ShieldedSoldier : public Infantry

{
private:
	int shootCooldown;
public:
	ShieldedSoldier(float startX, float startY)
		: Infantry(startX, startY, 50, 80, 4, 0.5f, 10, 1, 2)
	{
		velX = -speed;
		facingRight = false;
		shootCooldown=90;
	}
	void update() override {
		applyGravity();
		if(isOnGround)
		{
			x += velX;
			if (shootCooldown > 0) {
				shootCooldown--;
			}
			else {
				shootCooldown = 90;
			}
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

	void directionalDamage(int dmg, float bulletX, float bulletY, bool isExplosive) {
		if (isExplosive) {
			health-=dmg;
			return;
		}
		if (!facingRight && bulletX > x + width) {
			health -= dmg;
			return;
		}
		if (facingRight && bulletX < x) {
			health -= dmg;
			return;
		}

	}
	void draw(sf::RenderWindow& window, float camX) override
	{
		sprite.setPosition(x-camX,y);

		if(facingRight)
			sprite.setScale(0.3f,0.3f);
		else
			sprite.setScale(-0.3f,0.3f);

			window.draw(sprite);
	}
	bool loadTexture(const char* path) {
		if (texture.loadFromFile(path))
		{
			sprite.setTexture(texture);
			return true;
		}
		return false;
	}
	~ShieldedSoldier() {}


};