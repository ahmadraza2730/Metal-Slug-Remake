#pragma once
#include "FireArm.h"
class Pistol : public FireArm
{
public:
	Pistol(Player* p)
		: FireArm("Pistol", 0.5f, -1, 3, p)
	{
	}
	void fire() override
	{
		if (firetimer <= 0)
		{
			firetimer = firerate;
		}
	}
	
	void reload() override
	{

	}
	
	
	~Pistol()
	{
	}
};