#pragma once
# include "GrenadeWeapon.h"
class FireBomb : public GrenadeWeapon
{
public:
	FireBomb(Player* p)
		:GrenadeWeapon("Fire Bomb", 0.5f, 5, 5, p) {

	}
	void fire() {
		if (firetimer <= 0 && ammo > 0) {
			firetimer=firerate;
			ammo--;
			//world->spawnProjectile(new FireBombProjectile(...));
		}
	}
	~FireBomb(){}

};