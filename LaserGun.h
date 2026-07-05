#pragma once
#include "FireArm.h"

class LaserGun : public FireArm
{
public:
    LaserGun(Player* p)
        : FireArm("Laser Gun", 1.0f, 3, 999, p)
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

    void reload() override {}

    ~LaserGun() {}
};