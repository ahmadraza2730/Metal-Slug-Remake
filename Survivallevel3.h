#pragma once
#include <SFML/Graphics.hpp>
#include "InfiniteMap.h"
#include "Player.h"
#include "Enemy.h"
#include "RebelSoldier.h"
#include "BazookaSoldier.h"
#include "ShieldedSoldier.h"
#include "GrenadeSoldier.h"
#include "Paratrooper.h"
#include "Zombie.h"
#include "MummyWarrior.h"
#include "Martian.h"
#include "World.h"
#include "Bullet.h"
#include "HandGrenadeProjectile.h"
#include "DamageState.h"
#include "GameHUD.h"

class SurvivalLevel3
{
private:
    static const int maxEnemies = 40;
    Enemy* enemies[maxEnemies];

    InfiniteMap map;
    Player* player;
    World* world;

    float cameraX;
    int   killCount;
    int   killsNeeded;
    float spawnTimer;
    float spawnRate;

    bool levelClear;
    bool gameOver;
    int  score;

    sf::RectangleShape redHue;
    sf::Text           hudText;
    sf::Text           msgText;

    GameHUD hud;

public:
    SurvivalLevel3(World* w, sf::Font& f)
        : map(64, 1600, 900)
    {
        world = w;
        player = NULL;
        cameraX = 0;
        killCount = 0;
        killsNeeded = 30;
        spawnTimer = 0;
        spawnRate = 90.0f;
        levelClear = false;
        gameOver = false;
        score = 0;

        for (int i = 0; i < maxEnemies; i++)
            enemies[i] = NULL;

        map.loadTextures(
            "Assets/grass_block_side.png",
            "Assets/dirt.png",
            "Assets/stone.png",
            "Assets/deepslate_top.png"
        );

        redHue.setSize(sf::Vector2f(1600, 900));

        hudText.setFont(f);
        hudText.setCharacterSize(28);
        hudText.setFillColor(sf::Color::White);
        hudText.setOutlineColor(sf::Color::Black);
        hudText.setOutlineThickness(2);

        msgText.setFont(f);
        msgText.setCharacterSize(40);
        msgText.setFillColor(sf::Color::White);
        msgText.setOutlineColor(sf::Color::Black);
        msgText.setOutlineThickness(2);
        msgText.setPosition(500, 300);

        hud.loadFont("Assets/arial.ttf");
    }

    void setPlayer(Player* p)
    {
        player = p;
        cameraX = 0;
        killCount = 0;
        spawnTimer = 0;
        levelClear = false;
        gameOver = false;
        score = 0;

        for (int i = 0; i < maxEnemies; i++)
            enemies[i] = NULL;
    }

    void reset()
    {
        cameraX = 0;
        killCount = 0;
        spawnTimer = 0;
        levelClear = false;
        gameOver = false;
        score = 0;

        for (int i = 0; i < maxEnemies; i++)
        {
            if (enemies[i] != NULL)
            {
                delete enemies[i];
                enemies[i] = NULL;
            }
        }
    }

    void update(sf::Text& dmgText)
    {
        if (player == NULL || gameOver || levelClear) return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player->moveRight();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player->moveLeft();
        else
            player->stopMoving();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            player->jump();

        player->applyGravity();
        player->update();

        float groundY = map.getGroundY(player->getX() + player->getWidth() / 2.0f);
        player->landOnGround(groundY);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            if (player->getShootCooldown() <= 0)
            {
                float bx = player->isFacingRight() ? player->getX() + player->getWidth() : player->getX();
                float by = player->getY() + player->getHeight() / 2.0f;
                world->spawnProjectile(new Bullet(bx, by, player->isFacingRight()));
                player->resetShootCooldown(15);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            if (player->getGrenadeCooldown() <= 0)
            {
                float gx = player->isFacingRight() ? player->getX() + player->getWidth() : player->getX();
                float gy = player->getY();
                world->spawnProjectile(new HandGrenadeProjectile(gx, gy, player->isFacingRight(), player, player->getWeapon()));
                player->resetGrenadeCooldown(60);
            }
        }

        player->updateProjectiles(groundY);
        player->updateDamageState();

        if (player->getDamageState() == STATE_DEAD)
        {
            gameOver = true;
            return;
        }

        world->checkCollisions(player, enemies, maxEnemies, dmgText, cameraX);

        for (int i = 0; i < maxEnemies; i++)
        {
            if (enemies[i] != NULL && !enemies[i]->IsAlive())
            {
                killCount++;
                score += 200;
                delete enemies[i];
                enemies[i] = NULL;
            }
        }

        if (killCount >= killsNeeded)
        {
            levelClear = true;
            return;
        }

        spawnTimer++;
        if (spawnTimer >= spawnRate)
        {
            spawnTimer = 0;

            int batchSize = (rand() % 4) + 2;

            for (int b = 0; b < batchSize; b++)
            {
                for (int i = 0; i < maxEnemies; i++)
                {
                    if (enemies[i] == NULL)
                    {
                        int type = rand() % 8;
                        float spawnX = cameraX + 1600 + 100 + b * 100;

                        if (type == 0)
                        {
                            RebelSoldier* rs = new RebelSoldier(spawnX, 100);
                            rs->loadTexture("Assets/rebel.png");
                            enemies[i] = rs;
                        }
                        else if (type == 1)
                        {
                            BazookaSoldier* bs = new BazookaSoldier(spawnX, 100);
                            bs->loadTexture("Assets/bazooka.png");
                            enemies[i] = bs;
                        }
                        else if (type == 2)
                        {
                            ShieldedSoldier* ss = new ShieldedSoldier(spawnX, 100);
                            ss->loadTexture("Assets/shielded.png");
                            enemies[i] = ss;
                        }
                        else if (type == 3)
                        {
                            GrenadeSoldier* gs = new GrenadeSoldier(spawnX, 100);
                            gs->loadTexture("Assets/grenade.jpeg");
                            enemies[i] = gs;
                        }
                        else if (type == 4)
                        {
                            Paratrooper* pt = new Paratrooper(spawnX, 0);
                            pt->loadTexture("Assets/rebel.png", "Assets/parachute.png");
                            enemies[i] = pt;
                        }
                        else if (type == 5)
                        {
                            Zombie* zb = new Zombie(spawnX, 100);
                            zb->loadTexture("Assets/zombie.png");
                            enemies[i] = zb;
                        }
                        else if (type == 6)
                        {
                            MummyWarrior* mw = new MummyWarrior(spawnX, 100);
                            mw->loadTexture("Assets/mummy.png");
                            enemies[i] = mw;
                        }
                        else if (type == 7)
                        {
                            Martian* mt = new Martian(spawnX, 100);
                            mt->loadTexture("Assets/martian_foot.png", "Assets/martian_pod.png");
                            enemies[i] = mt;
                        }
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < maxEnemies; i++)
        {
            if (enemies[i] != NULL && enemies[i]->IsAlive())
            {
                float enemyGroundY = map.getGroundY(enemies[i]->getX() + enemies[i]->getWidth() / 2.0f);
                enemies[i]->landOnGround(enemyGroundY);
                enemies[i]->update();
            }
        }

        world->updateProjectiles();

        cameraX = player->getX() - 1600 / 2.0f + player->getWidth() / 2.0f;
        if (cameraX < 0) cameraX = 0;
    }

    void draw(sf::RenderWindow& window, sf::Text& dmgText)
    {
        if (player == NULL) return;

        if (gameOver)
        {
            msgText.setString("GAME OVER\n\nPress Enter to Restart\nPress Escape for Menu");
            window.draw(msgText);
            return;
        }

        if (levelClear)
        {
            msgText.setString("LEVEL 3 CLEAR!\n\nAll Levels Complete!\nPress Escape for Menu");
            window.draw(msgText);
            return;
        }

        map.draw(window, cameraX);
        player->draw(window, cameraX);
        player->drawBullets(window, cameraX);
        world->draw(window, cameraX);

        for (int i = 0; i < maxEnemies; i++)
        {
            if (enemies[i] != NULL && enemies[i]->IsAlive())
            {
                enemies[i]->draw(window, cameraX);
                hud.drawEnemyHealthBar(
                    window,
                    enemies[i]->getX(), enemies[i]->getY(),
                    static_cast<float>(enemies[i]->getWidth()),
                    enemies[i]->getHealth(), 10,
                    cameraX
                );
            }
        }

        if (player->getDamageState() == STATE_INJURED)
        {
            redHue.setFillColor(sf::Color(255, 0, 0, 60));
            window.draw(redHue);
        }
        else if (player->getDamageState() == STATE_CRITICAL)
        {
            redHue.setFillColor(sf::Color(255, 0, 0, 120));
            window.draw(redHue);
        }

        char buf[100] = "";
        sprintf_s(buf, "LEVEL 3 - CAVE   Kills: %d / %d     X:Shoot  Z:Grenade  Esc:Menu", killCount, killsNeeded);
        hudText.setPosition(350, 860);
        hudText.setString(buf);
        window.draw(hudText);

        window.draw(dmgText);
        hud.draw(window, player->getDamageState(), player->getLives(), score);
    }

    bool isGameOver() { return gameOver; }
    bool isLevelClear() { return levelClear; }
    int  getKillCount() { return killCount; }
    int  getScore() { return score; }

    ~SurvivalLevel3()
    {
        for (int i = 0; i < maxEnemies; i++)
        {
            if (enemies[i] != NULL)
            {
                delete enemies[i];
                enemies[i] = NULL;
            }
        }
    }
};