#pragma once
#include <SFML/Graphics.hpp>
class Grenade
{
private:
	float x;
	float y;
	float velocityx;
	float velocityy;
	float gravity;
	bool active;
	bool explode;
	int fusetime;
	float explosionradius;

	sf::CircleShape shape;
	sf::CircleShape explosionshape;
public:
	Grenade(float stx, float sty, bool isRight)
	{
		x = stx;
		y = sty;
		if (isRight)
		{
			velocityx = 7.0f;
		}
		else
		{
			velocityx = -7.0f;
		}
		velocityy = -8.0f; // upward velocity
		active = true;
		explode = false;
		gravity = 0.4f;
		fusetime = 120; // frames until explosion
		explosionradius = 80.0f;
		shape.setRadius(5);
		shape.setFillColor(sf::Color::Green);
		
		explosionshape.setRadius(explosionradius);
		explosionshape.setFillColor(sf::Color(255, 165, 0, 128)); // semi transparent orange
		explosionshape.setOrigin(explosionradius, explosionradius); // center the explosion shape
	}
	void Update(float groundy)
	{
		if (!active)
		{
			return;
		}
		if (!explode)
		{
			velocityy += gravity;
			x += velocityx;
			y += velocityy;
			if (y >= groundy)
			{
				y = groundy;
				velocityy *= -0.4f;  // bounce
				velocityx *= 0.7f;   // friction
			}
			fusetime--;
			if (fusetime <= 0)
			{
				explode = true;
			}
		}
		else
		{
			fusetime--;
			if (fusetime < -30)
			{
				active = false; // remove after explosion
			}
		}
	}
		void draw(sf::RenderWindow & window, float camX)
	    {
			if (!active)
			{
				return;
			}
			if (explode)
			{
				explosionshape.setPosition(x - camX, y);
				window.draw(explosionshape);
			}
			else
			{
				shape.setPosition(x - camX, y);
				window.draw(shape);
			}
		}
		bool isActive() const
		{
			return active;
		}
		float getx()
		{
			return x;
		}
		float gety()
		{
			return y;
		}
		float getExplosionRadius()
		{
			return explosionradius;
		}
		bool isexplode()
		{
			return explode;
		}
};