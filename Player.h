#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "DamageState.h"
#include "RocketProjectile.h"
#include "FlameProjectile.h"
#include "LaserProjectile.h"
#include "HandGrenadeProjectile.h"
#include "FireBombProjectile.h"

#include "Weapon.h"
#include "Pistol.h"
#include "HeavyMachineGun.h"
#include "RocketLauncher.h"
#include "FlameShot.h"
#include "LaserGun.h"

class World;

#include "Vehicle.h"
#include "VehicleRider.h"


class Player : public Entity, public VehicleRider
{
protected:
    float velx;
    float vely;
    float speed;
    float jumpforce;
    float gravity;
    bool onground;
    int maxHealth;
    int currenthealth;
    bool isDead;
    bool facingright;
    int damageState;
    float stateTimer;
    int lives;
    float respawnX;
    float respawnY;
    int shootCooldown;
    int grenadeCooldown;
    int grenadeCount;

    Vehicle* currentVehicle; 

    Weapon* currentWeapon;
    Weapon* pistolWeapon;
    Weapon* hmgWeapon;
    Weapon* rocketWeapon;
    Weapon* flameWeapon;
    Weapon* laserWeapon;
  


public:
    Player(float startX, float startY, int w, int h, int hp, float spd, float jump)
        : Entity(startX, startY, w, h)
    {
        velx = 0;
        vely = 0;
        speed = spd;
        jumpforce = jump;
        gravity = 0.5f;
        onground = false;
        maxHealth = hp;
        currenthealth = hp;
        isDead = false;
        facingright = true;
        pistolWeapon = new Pistol(this);
        hmgWeapon = new HeavyMachineGun(this);
        rocketWeapon = new RocketLauncher(this);
        flameWeapon = new FlameShot(this);
        laserWeapon = new LaserGun(this);
        currentWeapon = pistolWeapon;
        currentVehicle = NULL;

        damageState = 0;
        stateTimer = 0;
        lives = 3;
        respawnX = 0;
        respawnY = 0;
        grenadeCount = 10;
        shootCooldown = 0;
        grenadeCooldown = 0;
    }


    void boardVehicle(Vehicle* v)
    {
        if (v == NULL) return;
        if (v->isOccupied()) return;       
        if (currentVehicle != NULL) return; 

        currentVehicle = v;
        v->enter(this);                   

        
        float riderX = v->getX() + (v->getWidth() / 2.0f) - (width / 2.0f);
        float riderY = v->getY() - height;
        x = riderX;
        y = riderY;

        velx = 0;
        vely = 0;
        onground = true;
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

    int getGrenadeCount() const { return grenadeCount; }
    int getRocketAmmo()   const { return rocketWeapon ? rocketWeapon->getAmmo() : 0; }
    int getFlameAmmo()    const { return flameWeapon ? flameWeapon->getAmmo() : 0; }
    int getHMGAmmo()      const { return hmgWeapon ? hmgWeapon->getAmmo() : 0; }

    bool isNearVehicle(Vehicle* v) const
    {
        if (v == NULL) return false;

        float dx = x - v->getX();
        float dy = y - v->getY();

        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;

        return (dx < 80.0f && dy < 80.0f);
    }

    void vehicleMoveLeft()
    {
        if (currentVehicle == NULL) return;
        currentVehicle->moveLeft();
        facingright = false;
    }

    void vehicleMoveRight()
    {
        if (currentVehicle == NULL) return;
        currentVehicle->moveRight();
        facingright = true;
    }

    void vehicleShoot()
    {
        if (currentVehicle == NULL) return;
        currentVehicle->shoot();
    }

    void updateVehicleRide()
    {
        if (currentVehicle == NULL) return;

        float riderX = currentVehicle->getX() + (currentVehicle->getWidth() / 2.0f) - (width / 2.0f);
        float riderY = currentVehicle->getY() - height;
        x = riderX;
        y = riderY;
    }


    void moveRight()
    {
        velx = speed;
        facingright = true;
    }

    void moveLeft()
    {
        velx = -speed;
        facingright = false;
    }

    void stopMoving()
    {
        velx = 0;
    }

    void jump()
    {
        if (onground)
        {
            vely = -jumpforce;
            onground = false;
        }
    }

    void applyGravity()
    {
        vely += gravity;
        y += vely;
        x += velx;
    }

    void landOnGround(float groundY)
    {
        if (y + height >= groundY)
        {
            y = groundY - height;
            vely = 0;
            onground = true;
        }
        else
        {
            onground = false;
        }
    }

    // -------------------------------------------------------
    // DAMAGE
    // -------------------------------------------------------

    void takeDamage(int damage)
    {
       
        if (currentVehicle != NULL)
        {
            currentVehicle->takeDamage(damage);
            if (!currentVehicle->getIsAlive())
                exitVehicle();
            return;
        }

        if (stateTimer > 0) return;

        currenthealth -= damage;

        if (currenthealth <= 0)
        {
            currenthealth = 0;
            damageState = STATE_DEAD;
            isDead = true;
            isAlive = false;
        }
        else if (currenthealth <= maxHealth / 3)   
        {
            damageState = STATE_CRITICAL;
            stateTimer = 40;   
        }
        else
        {
            damageState = STATE_INJURED;
            stateTimer = 40;   
        }
    }

    void updateDamageState()
    {
        if (stateTimer > 0)
            stateTimer--;

        if (stateTimer == 0 && !isDead)
        {
            if (currenthealth <= maxHealth / 3)
                damageState = STATE_CRITICAL;
            else
                damageState = STATE_NORMAL;
        }
    }

    void respawn()
    {
        if (isDead && lives > 0)
        {
            lives--;
            currenthealth = maxHealth;   
            damageState = STATE_NORMAL;
            stateTimer = 0;
            isDead = false;
            isAlive = true;
            velx = 0;
            vely = 0;
            currentVehicle = NULL;
            
        }
    }

    void heal(int amount)
    {
        currenthealth += amount;
        if (currenthealth > maxHealth)
            currenthealth = maxHealth;
    }

    // -------------------------------------------------------
    // WEAPONS / SHOOTING
    // -------------------------------------------------------


    // -------------------------------------------------------
    // GETTERS / SETTERS
    // -------------------------------------------------------

    void setPosition(float nx, float ny)
    {
        sprite.setPosition(nx, ny);
    }
    float getWidth()
    {
        return sprite.getGlobalBounds().width;
    }
    float getHeight()
    {
        return sprite.getGlobalBounds().height;
    }
    float getVelocityX()
    {
        return velx;
    }
    float getVelocityY()
    {
        return vely;
    }
    int getHealth()
    {
        return currenthealth;
    }
    int getMaxHealth()
    {
        return maxHealth;
    }
    bool getIsDead()
    {
        return isDead;
    }
    bool isOnGround()
    {
        return onground;
    }
    bool isFacingRight()
    {
        return facingright;
    }
    int getDamageState()
    {
        return damageState;
    }
    int getLives()
    {
        return lives;
    }
    float getStateTimer()
    {
        return stateTimer;
    }
    void setWeapon(Weapon* w)
    {
        currentWeapon = w;
    }
    Weapon* getWeapon()
    {
        return currentWeapon;
    }
    int getShootCooldown()
    {
        return shootCooldown;
    }
    int getGrenadeCooldown()
    {
        return grenadeCooldown;
    }
    void resetShootCooldown(int val)
    {
        shootCooldown = val;
    }
    void resetGrenadeCooldown(int val)
    {
        grenadeCooldown = val;
    }
    void updateProjectiles(float groundY)
    {
        if (shootCooldown > 0) shootCooldown--;
        if (grenadeCooldown > 0) grenadeCooldown--;
    }
    void drawBullets(sf::RenderWindow& window, float camX)
    {
        // bullets are drawn via world.draw()
    }
    void shoot(World* world);
    void fireRocket(World* world);
    void fireHMG(World* world);
    void fireFlame(World* world);
    void fireLaser(World* world);
    void throwGrenade(World* world);
    void throwFireBomb(World* world);


    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window, float camX) = 0;



    virtual ~Player()
    {

    }
};