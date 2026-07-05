#pragma once
#include "Player.h"
#include "Enemy.h"
#include "World.h"
#include "Projectile.h"
#include "MummyWarrior.h"

class DamageSystem
{
public:

    // checks if two sf::FloatRects overlap
    bool rectsOverlap(sf::FloatRect a, sf::FloatRect b)
    {
        return a.intersects(b);
    }

    // player body touches enemy body — player takes damage
    void checkPlayerEnemyCollision(Player* player, Enemy** enemies, int maxEnemies)
    {
        if (player == NULL) return;
        if (player->getIsDead()) return;

        sf::FloatRect playerRect(
            player->getX(),
            player->getY(),
            player->getWidth(),
            player->getHeight()
        );

        for (int i = 0; i < maxEnemies; i++)
        {
            if (enemies[i] == NULL) continue;
            if (!enemies[i]->IsAlive()) continue;

            sf::FloatRect enemyRect(
                enemies[i]->getX(),
                enemies[i]->getY(),
                enemies[i]->getWidth(),
                enemies[i]->getHeight()
            );

            if (rectsOverlap(playerRect, enemyRect))
            {
                player->takeDamage(enemies[i]->getDamage());
            }
        }
    }

    // player bullets hit enemies
    void checkProjectilesVsEnemies(World* world, Enemy** enemies, int maxEnemies)
    {
        if (world == NULL) return;

        int count = world->getProjectileCount();

        for (int p = 0; p < count; p++)
        {
            Projectile* proj = world->getProjectile(p);
            if (proj == NULL) continue;
            if (!proj->isActive()) continue;
            if (!proj->isFromPlayer()) continue;  // only player projectiles hit enemies

            sf::FloatRect projRect = proj->getBounds();

            for (int i = 0; i < maxEnemies; i++)
            {
                if (enemies[i] == NULL) continue;
                if (!enemies[i]->IsAlive()) continue;

                sf::FloatRect enemyRect(
                    enemies[i]->getX(),
                    enemies[i]->getY(),
                    enemies[i]->getWidth(),
                    enemies[i]->getHeight()
                );

                if (rectsOverlap(projRect, enemyRect))
                {
                    MummyWarrior* mummy = dynamic_cast<MummyWarrior*>(enemies[i]);

                    if (mummy != NULL)
                    {
                        //mummies only die from fire
                        if (proj->isFireType())
                        {
                            mummy->takeFireDamage(proj->getDamage());
                        }
                        else
                        {
                            mummy->takeDamage(proj->getDamage());
                        }
                    }
                    else
                    {
                        enemies[i]->takeDamage(proj->getDamage());
                    }

                    
                    if (!proj->isFireType())
                        proj->deactivate();

                    break;
                }
            }
        }
    }

    void checkProjectilesVsPlayer(World* world, Player* player)
    {
        if (world == NULL || player == NULL) return;
        if (player->getIsDead()) return;

        int count = world->getProjectileCount();

        sf::FloatRect playerRect(
            player->getX(),
            player->getY(),
            player->getWidth(),
            player->getHeight()
        );

        for (int p = 0; p < count; p++)
        {
            Projectile* proj = world->getProjectile(p);
            if (proj == NULL) continue;
            if (!proj->isActive()) continue;
            if (proj->isFromPlayer()) continue; 

            sf::FloatRect projRect = proj->getBounds();

            if (rectsOverlap(projRect, playerRect))
            {
                player->takeDamage(proj->getDamage());
                proj->deactivate();
            }
        }
    }

    ~DamageSystem() {}
};