#pragma once
#include "Collectable.h"
#include "Player.h"

class FoodCollectable : public Collectable
{
private:
    int healAmount;

public:
    FoodCollectable(float x, float y, int heal = 30)
        : Collectable(x, y, 32, 32), healAmount(heal) {
    }

    void onCollect(Player* player) override
    {
        player->heal(healAmount);
        deactivate();
    }
};