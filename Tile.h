#pragma once
#include <SFML/Graphics.hpp>
class Tile
{
private:
	float x;
	float y;
	int tiletype;
	bool solid;  
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Tile(float startX, float startY, int type,bool isSolid)
	{
		x = startX;
		y = startY;
		tiletype = type;
		solid = isSolid;
	}
	bool loadTexture(const char* path)
	{
		if (texture.loadFromFile(path))
		{
			sprite.setTexture(texture);
			sprite.setPosition(x,y);
			return true;
		}
		else 
		{
			return false;
		}

	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	int getType()
	{
		return tiletype;
	}
	bool isSolid()
	{
		return solid;
	}
};