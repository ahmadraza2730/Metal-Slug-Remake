#pragma once
#include "FireArm.h"
class HeavyMachineGun : public FireArm
{

public:
	HeavyMachineGun(Player *p)
		: FireArm("Heavy Machine Gun", 0.1f, 100, 3, p)
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
	}
	
	~HeavyMachineGun()
	{
	}
};