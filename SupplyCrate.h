#pragma once
#include "Collectable.h"
#include "Player.h"

class SupplyCrate : public Collectable
{
private:
    bool opened;

public:
    SupplyCrate(float x, float y)
        : Collectable(x, y, 48, 48), opened(false) {
    }

    void onCollect(Player* player) override
    {
        if (opened) return;
        opened = true;
        player->heal(50);
        player->resetGrenadeCooldown(0);
        deactivate();
    }
};