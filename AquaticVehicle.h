#pragma once
#include "Vehicle.h"
class AquaticVehicle : public Vehicle
{
protected:
	float waterlvl;
	bool submerged;
	float buoyancy;
public:
	AquaticVehicle(float startX, float startY, float spd, int hp)
		: Vehicle(startX, startY, spd, hp)
	{
		waterlvl = 600.0f;
		submerged = false;
		buoyancy = 0.3f;
	}
    void moveLeft()
    {
        speedx = -maxspeed;
    }

    void moveRight()
    {
        speedx = maxspeed;
    }

    void dive()
    {
        speedy = maxspeed;
        submerged = true;
    }

    void rise()
    {
        speedy = -buoyancy;
        if (y <= waterlvl)
            submerged = false;
    }
    void applyMovement()
    {
        x += speedx;
        y += speedy;
    }
    bool issubmerged()
    {
		return submerged;
    }
    virtual void shoot() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window, float camX) = 0;

    virtual ~AquaticVehicle() 
    { }
};