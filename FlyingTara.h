#pragma once
#include "AerialVehicle.h"

class FlyingTara : public AerialVehicle
{
private:
	float hoverheight;
	float cooldown;
	bool active;
	float gernadex;
	float gernadey;
    bool gernadedropped;
	sf::Texture grenadeTexture;
	sf::Sprite  grenadeSprite;
public:
    FlyingTara(float startX, float startY)
        : AerialVehicle(startX, startY, 3.0f, 5)
    {
        hoverheight = 300.0f;
        cooldown = 0;
        active = true;
        gernadedropped = false;
        gernadex = 0;
        gernadey = 0;
    }
    void loadTexture(const char* vehiclePath, const char* grenadePath)
    {
        texture.loadFromFile(vehiclePath);
        grenadeTexture.loadFromFile(grenadePath);
        sprite.setTexture(texture);
        grenadeSprite.setTexture(grenadeTexture);
    }
    void moveLeft()
    {
        speedx -= 6.0f;
    }
    void moveRight() 
    { 
        speedx += 6.0f; 
    }
    void dropGrenade(float playerX, float playerY)
    {
        if (cooldown > 0) return;

        if (x >= playerX - 20 && x <= playerX + 20)
        {
            gernadex = x;
            gernadey = y;
            gernadedropped = true;
            cooldown = 120;  
        }
    }
    void shoot()
    {
        gernadedropped = true;
    }

    void update()
    {
        y = 200;
        if (y > hoverheight)
            speedy = -2.0f;
        else if (y < hoverheight)
            speedy = 2.0f;
        else
            speedy = 0;

        x += speedx;
        y += speedy;

        if (gernadedropped)
        {
            gernadey += 5.0f;
        }

        if (cooldown > 0)
        {
            cooldown--;
        }
    }
    void draw(sf::RenderWindow& window, float camX)
    {
        sprite.setPosition(x - camX, y);
        window.draw(sprite);

        if (gernadedropped)
        {
            grenadeSprite.setPosition(gernadex - camX, gernadey);
            window.draw(grenadeSprite);
        }
    }
    bool  isActive() 
    { 
        return active; 
    }
    void  setActive(bool v) 
    { 
        active = v; 
    }
    float getGrenadeY() 
    { 
        return gernadey; 
    }
    float getGrenadeX() 
    { 
        return gernadex; 
    }
    bool  hasDropped() 
    { 
        return gernadedropped; 
    }
    void  resetGrenade() 
    { 
        gernadedropped = false; 
    }

    ~FlyingTara() 
    { }
};