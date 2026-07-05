#pragma once
#include "FireArm.h"

class FlameShot : public FireArm
{
public:
    FlameShot(Player* p)
        : FireArm("Flame Shot", 0.05f, 300, 2, p)
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

    ~FlameShot() {}
};