#pragma once
# include "Weapon.h"
class GrenadeWeapon :public Weapon 
{
public:
	GrenadeWeapon(const char* n, float fr, int am, int dmg, Player* p)
		:Weapon(n,fr,am,dmg,p){}
	//no need for realoding grenades
	void reload() override{}
	virtual ~GrenadeWeapon(){}
};