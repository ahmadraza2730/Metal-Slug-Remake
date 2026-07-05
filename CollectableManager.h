#pragma once
#include "Collectable.h"
#include "FoodCollectable.h"
#include "POWPrisoner.h"
#include "SupplyCrate.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class CollectableManager
{
private:
    static const int MAX = 50;
    Collectable* items[MAX];

    void addItem(Collectable* c)
    {
        for (int i = 0; i < MAX; i++)
        {
            if (items[i] == nullptr)
            {
                items[i] = c;
                return;
            }
        }
        delete c;
    }

public:
    CollectableManager()
    {
        for (int i = 0; i < MAX; i++)
            items[i] = nullptr;
    }

    void update(Player* player)
    {
        for (int i = 0; i < MAX; i++)
        {
            if (items[i] == nullptr || !items[i]->isActive())
                continue;

            items[i]->update();

            sf::FloatRect pb(
                player->getX(), player->getY(),
                player->getWidth(), player->getHeight()
            );
            if (items[i]->getBounds().intersects(pb))
                items[i]->onCollect(player);

            Collectable* extra = items[i]->spawnExtra();
            if (extra != nullptr)
                addItem(extra);

            if (!items[i]->isActive())
            {
                delete items[i];
                items[i] = nullptr;
            }
        }
    }

    void draw(sf::RenderWindow& window, float camX)
    {
        for (int i = 0; i < MAX; i++)
            if (items[i] != nullptr && items[i]->isActive())
                items[i]->draw(window, camX);
    }

    void spawnRandom(float camX, float screenX, float groundY)
    {
        int   type = rand() % 3;
        float spawnX = camX + screenX + 200 + (rand() % 400);
        float spawnY = groundY - 48;

        Collectable* c = nullptr;

        if (type == 0)
        {
            const char* foodSprites[] = {
                "Assets/burger.png",
                "Assets/burger_large.png",
                "Assets/fish.png",
                "Assets/fruit_basket.png",
                "Assets/golden_pot.png",
                "Assets/banana.png",
                "Assets/cabbage.png",
                "Assets/tomato.png",
                "Assets/watermelon.png",
                "Assets/pumpkin.png",
                "Assets/potion_red.png"
            };
            int healAmounts[] = { 20, 40, 15, 25, 50, 10, 10, 10, 30, 35, 60 };
            int foodIdx = rand() % 11;

            c = new FoodCollectable(spawnX, spawnY, healAmounts[foodIdx]);
            c->loadTexture(foodSprites[foodIdx]);
        }
        else if (type == 1)
        {
            c = new POWPrisoner(spawnX, spawnY);
            c->loadTexture("Assets/pow.png");
        }
        else
        {
            c = new SupplyCrate(spawnX, spawnY);
            c->loadTexture("Assets/supply_crate.png");
        }

        addItem(c);
    }

    ~CollectableManager()
    {
        for (int i = 0; i < MAX; i++)
        {
            if (items[i] != nullptr)
            {
                delete items[i];
                items[i] = nullptr;
            }
        }
    }
};