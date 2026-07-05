#pragma once
#include <SFML/Graphics.hpp>

class Entity {
protected:
	float x;
	float y;
	int width;
	int height;
	int biometype;
	bool isAlive;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Entity(float startX, float startY, int w, int h)
	{
		x = startX;
		y = startY;
		width = w;
		height = h;
		biometype = 0;
		isAlive = true;
	}
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window, float camX) = 0;

	float getX() const 
	{ 
		return x; 
	}
	float getY() const 
	{ 
		return y; 
	}
	int getWidth() const 
	{ 
		return width; 
	}
	int getHeight() const 
	{ 
		return height; 
	}
	int getBiome() const
	{
		return biometype;
	}
	bool IsAlive() const
	{
		return isAlive;
	}
	void setX(float newx) 
	{ 
		x = newx; 
	}
	void setY(float newy) 
	{ 
		y = newy; 
	}
	void setBiome(int newBiome)
	{
		biometype = newBiome;
	}
	void setAlive(bool alive)
	{
		isAlive = alive;
	}
	virtual void takeDamage(int damage)
	{
		isAlive = false; 
	}
	virtual ~Entity()
	{ }
};