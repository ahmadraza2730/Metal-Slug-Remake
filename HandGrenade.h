#pragma once
#include "GrenadeWeapon.h"

class HandGrenade : public GrenadeWeapon
{
	HandGrenade(Player *p)
		:GrenadeWeapon("Hand Grenade", 0.5f, 5, 10, p){}

	void fire() override {
		if (firetimer <= 0 && ammo > 0) {
			firetimer=firerate;
			ammo--;
		}
		//will be implemented when we will create projectiles
		//world->spawnProjectile(new HandGrenadeProjectile(...));
	}
	~HandGrenade(){}
};