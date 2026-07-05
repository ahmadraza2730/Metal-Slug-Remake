#pragma once
#include <SFML/Graphics.hpp>
class Camera
{
private:
	float x;
	float y;
	float width;
	float height;
public:
	Camera(float w, float h)
	{
		x = 0;
		y = 0;
		width = w;
		height = h;
	}
	void follow(float tarx, float tary)
	{
		x = tarx - width / 2.0f;
		y = tary - height / 2.0f;
		if (x < 0)
		{
			x = 0;
		}
		if (y < 0)
		{
			y = 0;
		}
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	bool isVisisble(float objX, float objY)
	{
		if (objX + 64 < x)
		{
			return false;
		}
		if (objX > x + width)
		{
			return false;
		}
		if (objY + 64 < y)
		{
			return false;
		}
		if (objY > y + height)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};