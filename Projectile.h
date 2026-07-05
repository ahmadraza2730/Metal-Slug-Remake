#pragma once
#include <SFML/Graphics.hpp>


class Player;
class Weapon;

class Projectile
{
protected:
    float x;
    float y;
    float velX;
    float velY;
    float gravity;
    float spawnX;
    float spawnY;
    int damage;

    bool active;
    bool fromPlayer;
    bool explosive;
    bool fireType;

    Player* firedBy;
    Weapon* firedFrom;

public:
    Projectile(float startX, float startY, float vx, float vy, float grav, int dmg, bool playerOwned, bool isExplosive, Player* shooter, Weapon* weapon)
    {
        x = startX;
        y = startY;
        velX = vx;
        velY = vy;
        gravity = grav;
        spawnX = startX;
        spawnY = startY;
        damage = dmg;
        active = true;
        fromPlayer = playerOwned;
        explosive = isExplosive;
        firedBy = shooter;
        firedFrom = weapon;
        fireType=false;
    }

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window, float camX) = 0;

    virtual sf::FloatRect getBounds() const = 0;




    float getX()
    {
        return x;
    }

    float getY()
    {
        return y;
    }

    float getSpawnX()
    {
        return spawnX;
    }

    float getSpawnY()
    {
        return spawnY;
    }

    int getDamage()
    {
        return damage;
    }

    bool isActive()
    {
        return active;
    }

    bool isFromPlayer()
    {
        return fromPlayer;
    }

    bool isExplosive()
    {
        return explosive;
    }

    bool isFireType() const
    {
        return fireType;
    }

    void setFireType(bool val)
    {
        fireType = val;
    }

    Player* getFiredBy()
    {
        return firedBy;
    }

    Weapon* getFiredFrom()
    {
        return firedFrom;
    }

    void deactivate()
    {
        active = false;
    }

    virtual ~Projectile() {}
};