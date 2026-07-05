#pragma once
#include "Weapon.h"
class Knife : public Weapon
{
private:
	float attacktime;
	float attackrange;
public:
	Knife() : Weapon("Knife", 0.5f, -1, 25, nullptr)
	{
		attacktime = 0;
		attackrange = 50.0f;
	}
	void fire() override
	{
		if (attacktime <= 0)
		{
			attacktime = firerate; // Reset attack timer
		}
	}
	void reload() override
	{
	}
	void update() override
	{
		if (attacktime > 0)
			attacktime -= 0.016f;
	}
	void render(sf::RenderWindow& window, float camX)
	{
		if (owned)
		{
			sprite.setPosition(sprite.getPosition().x - camX, sprite.getPosition().y);
			window.draw(sprite);
		}
	}
	~Knife()
	{
	}
};