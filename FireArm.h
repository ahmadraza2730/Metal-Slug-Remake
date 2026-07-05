#pragma once
#include "Weapon.h"

class FireArm : public Weapon
{
public:
    FireArm(const char* n, float fr, int am, int dmg, Player* p)
        : Weapon(n, fr, am, dmg, p)
    {
    }

    virtual ~FireArm() {}
};