#pragma once
#include "Entity.h"
#include "Vehicle.h"
#include "VehicleRider.h"

class Enemy : public Entity, public VehicleRider
{
protected:
    int health;
    float speed;
    int damage;
    float velX;
    float velY;
    float gravity;
    bool isOnGround;
    bool facingRight;
    Vehicle* currentVehicle; 

public:
    Enemy(float startX, float startY, int w, int h, int hp, float s, int d)
        : Entity(startX, startY, w, h)
    {
        health = hp;
        speed = s;
        damage = d;
        velX = 0.0f;
        velY = 0.0f;
        gravity = 0.5f;
        isOnGround = false;
        facingRight = false;
        currentVehicle = NULL;
    }


    void boardVehicle(Vehicle* v)
    {
        if (v == NULL) 
            return;
        if (v->isOccupied()) 
            return;
        if (currentVehicle != NULL) 
            return;

        currentVehicle = v;
        v->enter(this);

        float riderX = v->getX() + (v->getWidth() / 2.0f) - (width / 2.0f);
        float riderY = v->getY() - height;
        x = riderX;
        y = riderY;

        velX = 0;
        velY = 0;
        isOnGround = true;
    }

    void exitVehicle()
    {
        if (currentVehicle == NULL) return;

        x = currentVehicle->getX() - width - 5.0f;
        y = currentVehicle->getY();

        currentVehicle->exit();
        currentVehicle = NULL;
    }

    bool isInVehicle()
    {
        return currentVehicle != NULL;
    }

    Vehicle* getVehicle()
    {
        return currentVehicle;
    }
    bool isNearVehicle(Vehicle* v) const
    {
        if (v == NULL) return false;

        float dx = x - v->getX();
        float dy = y - v->getY();

        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;

        return (dx < 80.0f && dy < 80.0f);
    }

    void updateVehicleRide()
    {
        if (currentVehicle == NULL) return;

        float riderX = currentVehicle->getX() + (currentVehicle->getWidth() / 2.0f) - (width / 2.0f);
        float riderY = currentVehicle->getY() - height;
        x = riderX;
        y = riderY;
    }

    void vehicleChase(float targetX)
    {
        if (currentVehicle == NULL) return;

        if (x < targetX)
        {
            currentVehicle->moveRight();
            facingRight = true;
        }
        else
        {
            currentVehicle->moveLeft();
            facingRight = false;
        }
    }

    void vehicleShoot()
    {
        if (currentVehicle == NULL) return;
        currentVehicle->shoot();
    }



    virtual void update() override = 0;
    virtual void draw(sf::RenderWindow& window, float camX) override = 0;
    virtual void enemyShoot(World* world, float playerX, float playerY) {}

    virtual void takeDamage(int dmg) override
    {
        if (currentVehicle != NULL)
        {
            currentVehicle->takeDamage(dmg);

            if (!currentVehicle->getIsAlive())
            {
                exitVehicle();
            }
            return;
        }

        health -= dmg;
        if (health < 0)
        {
            health = 0;
            isAlive = false;
        }
    }

    void applyGravity()
    {
        velY += gravity;
        y += velY;
    }

    void landOnGround(float groundY)
    {
        if (y + height >= groundY)
        {
            y = groundY - height;
            velY = 0;
            isOnGround = true;
        }
        else
        {
            isOnGround = false;
        }
    }

    // -------------------------------------------------------
    // GETTERS
    // -------------------------------------------------------

    int getHealth() const
    {
        return health;
    }

    int getDamage() const
    {
        return damage;
    }
    virtual int getEnemyType() const
    {
        return 0;
    }

    virtual ~Enemy() {}
};