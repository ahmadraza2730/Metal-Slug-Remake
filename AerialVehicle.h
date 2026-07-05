#pragma once
#include "Vehicle.h"
class AerialVehicle : public Vehicle
{
protected:
    float miny;
    float maxy;
public:
    AerialVehicle(float startX, float startY, float spd, int hp)
        : Vehicle(startX, startY, spd, hp)
    {
        miny = 50.0f;
        maxy = 700.0f;
    }
    void moveLeft()
    {
        speedx = -maxspeed;
    }

    void moveRight()
    {
        speedx = maxspeed;
    }

    void moveUp()
    {
        speedy = -maxspeed;
    }

    void moveDown()
    {
        speedy = maxspeed;
    }

    void stopVertical()
    {
        speedy = 0;
    }

    void clampPosition()
    {
        if (y < miny) y = miny;
        if (y > maxy) y = maxy;
    }

    virtual void shoot() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window, float camX) = 0;

    virtual ~AerialVehicle() {}
};