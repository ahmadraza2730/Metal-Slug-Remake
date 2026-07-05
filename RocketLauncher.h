#pragma once
#include "FireArm.h"
class RocketLauncher : public FireArm
{

public:
	RocketLauncher(Player *p)
		: FireArm("Rocket Launcher", 2.0f, 5, 5, p)
	{
	}
	void fire() override
	{
		if (firetimer <= 0 && ammo > 0)
		{
			firetimer = firerate;
			ammo--;
		}
	}

	void reload() override
	{
		isreloading = true;
		reloadtimer = 3.0f;
	}

	~RocketLauncher()
	{
	}
};