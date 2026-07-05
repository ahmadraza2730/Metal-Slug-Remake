#pragma once
#include "Vehicle.h"
class GroundVehicle : public Vehicle
{
protected:
	float gravity;
	bool onground;
	float jumpforce;
public:
	GroundVehicle(float startX, float startY, float spd, int hp)
		: Vehicle(startX, startY, spd, hp)
	{
		gravity = 0.5f;
		onground = false;
		jumpforce = 10.0f;
	}
	void applyGravity()
	{
		speedy += gravity;
		y += speedy;
		x += speedx;
	}
	// ground collision
	void landOnGround(float groundY)
	{
		if (y + sprite.getGlobalBounds().height >= groundY)
		{
			y = groundY - sprite.getGlobalBounds().height;
			speedy = 0;
			onground = true;
		}
		else
		{
			onground = false;
		}
	}
	void moveLeft()
	{
		speedx = -maxspeed;
	}

	void moveRight()
	{
		speedx = maxspeed;
	}
	virtual void shoot() = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window, float camX) = 0;
	bool isOnGround() const
	{
		return onground;
	}
	virtual ~GroundVehicle() 
	{ }
};