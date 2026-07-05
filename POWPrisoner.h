#pragma once
#include "Collectable.h"
#include "SupplyCrate.h"
#include "Player.h"

class POWPrisoner : public Collectable
{
private:
    bool rescued;
    bool crateReady;

public:
    POWPrisoner(float x, float y)
        : Collectable(x, y, 40, 60), rescued(false), crateReady(false) {
    }

    void onCollect(Player* player) override
    {
        if (rescued) return;
        rescued = true;
        crateReady = true;
        player->heal(20);
        deactivate();
    }

    // called by manager each frame — no cast needed
    Collectable* spawnExtra() override
    {
        if (!crateReady) return nullptr;
        crateReady = false;
        SupplyCrate* crate = new SupplyCrate(x + 60, y);
        crate->loadTexture("Assets/supply_crate.png");
        return crate;
    }
};