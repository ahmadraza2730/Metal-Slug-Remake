#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Menu.h"
#include "PlayerSelect.h"
#include "PerlinNoise.h"
#include "InfiniteMap.h"
#include "Entity.h"
#include "Tile.h"
#include "Camera.h"
#include "World.h"
#include "Weapon.h"
#include "Pistol.h"
#include "HeavyMachineGun.h"
#include "RocketLauncher.h"
#include "Player.h"
#include "Marco.h"
#include "Tarma.h"
#include "Eri.h"
#include "Fio.h"
#include "Enemy.h"
#include "Infantry.h"
#include "RebelSoldier.h"
#include "BazookaSoldier.h"
#include "ShieldedSoldier.h"
#include "GrenadeSoldier.h"
#include "Vehicle.h"
#include "GroundVehicle.h"
#include "AerialVehicle.h"
#include "AquaticVehicle.h"
#include "FlyingTara.h"
#include "Bradley.h"
#include "EnemySub.h"
#include "DamageState.h"
#include "Projectile.h"
#include "StraightProjectile.h"
#include "Bullet.h"
#include "FlameProjectile.h"
#include "LaserProjectile.h"
#include "RocketProjectile.h"
#include "HandGrenadeProjectile.h"
#include "FireBombProjectile.h"
#include "SurvivalLevel1.h"
#include "SurvivalLevel2.h"
#include "SurvivalLevel3.h"
#include "CollectableManager.h"
#include "Scoreboard.h"
#include "ScoreSystem.h"
#include "Leaderboard.h"

using namespace sf;

int screen_x = 1600;
int screen_y = 900;

void draw_player(RenderWindow& window, Sprite& playerSprite, float player_x, float player_y);

int main()
{
    RenderWindow window(VideoMode(screen_x, screen_y), "Metal Slug", Style::Close);
    window.setFramerateLimit(60);

    sf::Music bgMusic;
    bgMusic.openFromFile("Assets/background.ogg");
    bgMusic.setLoop(true);
    bgMusic.setVolume(20);
    bgMusic.play();

    sf::SoundBuffer clickBuffer;
    clickBuffer.loadFromFile("Assets/click.ogg");
    sf::Sound clickSound;
    clickSound.setBuffer(clickBuffer);

    Menu menu;
    menu.load("Assets/arial.ttf", "Assets/menubg.png");

    PlayerSelect charSelect;
    charSelect.load("Assets/arial.ttf", "Assets/menubg.png");
    int chosenCharacter = 0;
    int currentScreen = 0;

    Font infoFont;
    infoFont.loadFromFile("Assets/arial.ttf");
    Text infoText;
    infoText.setFont(infoFont);
    infoText.setCharacterSize(35);
    infoText.setFillColor(Color::White);
    infoText.setOutlineColor(Color::Black);
    infoText.setOutlineThickness(2);
    infoText.setPosition(150, 150);

    InfiniteMap infiniteMap(64, static_cast<int>(screen_x), static_cast<int>(screen_y));
    infiniteMap.loadTextures(
        "Assets/grass_block_side.png",
        "Assets/dirt.png",
        "Assets/stone.png",
        "Assets/deepslate_top.png"
    );

    World world(screen_x, screen_y);
    world.setMap(&infiniteMap);
    Player* currentplayer = NULL;
    bool insideVehicle = false;
    FlyingTara* currentVehicle = NULL;
    const int max_enemies = 50;
    Enemy* enemies[max_enemies];
    for (int i = 0; i < max_enemies; i++)
        enemies[i] = NULL;

    ScoreSystem scoreSystem;
    scoreSystem.loadFont("Assets/arial.ttf");

    Leaderboard leaderboard;
    leaderboard.loadFont("Assets/arial.ttf");
    leaderboard.load();

    const int maxvehicles = 10;
    FlyingTara* flyingTaras[maxvehicles];
    Bradley* bradleys[maxvehicles];
    EnemySub* enemySubs[maxvehicles];
    for (int i = 0; i < maxvehicles; i++)
    {
        flyingTaras[i] = NULL;
        bradleys[i] = NULL;
        enemySubs[i] = NULL;
    }

    float scale_x = 0.2f;
    float scale_y = 0.2f;
    int raw_img_x = 593;
    int raw_img_y = 470;
    int Pheight = static_cast<int>(raw_img_y * scale_y);
    int Pwidth = static_cast<int>(raw_img_x * scale_x);

    float player_x = 380;
    float player_y = 300;
    float cameraX = 0;
    float gravityY = 0;
    bool  onground = false;
    float max_speed = 5;
    float velx = 0;
    float acceleration = 0.5f;

    Texture playerTex;
    Sprite  playerSprite;
    playerTex.loadFromFile("Assets/Character.png");
    playerSprite.setTexture(playerTex);
    playerSprite.setScale(scale_x, scale_y);

    sf::RectangleShape redHue;
    redHue.setSize(sf::Vector2f(static_cast<float>(screen_x), static_cast<float>(screen_y)));

    char name[100] = "";
    int  nameLen = 0;
    srand(static_cast<unsigned>(time(NULL)));
    float nextSpawnX = 800.0f;
    float nextVehicleSpawnX = 700.0f;

    sf::Text dmgText;
    dmgText.setFont(infoFont);
    dmgText.setCharacterSize(25);
    dmgText.setFillColor(sf::Color::Red);
    dmgText.setOutlineColor(sf::Color::Black);
    dmgText.setOutlineThickness(2);
    dmgText.setString("");

    CollectableManager collectables;
    float nextCollectableSpawnX = 600.0f;

    SurvivalLevel1 survLevel1(&world, infoFont);
    SurvivalLevel2 survLevel2(&world, infoFont);
    SurvivalLevel3 survLevel3(&world, infoFont);
    Player* survivalPlayer = NULL;
    int survivalCurrentLevel = 1;

    PlayerSelect survCharSelect;
    survCharSelect.load("Assets/arial.ttf", "Assets/menubg.png");

    Scoreboard scoreboard;
    scoreboard.loadFont("Assets/arial.ttf");
    scoreboard.load();

    int campaignKills = 0;

    Event ev;
    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                window.close();

            if (currentScreen == 0)
            {
                if (ev.type == Event::KeyPressed)
                {
                    if (ev.key.code == Keyboard::Up || ev.key.code == Keyboard::Down)
                        clickSound.play();
                }
                menu.handleInput(ev);

                int choice = menu.getChoice(ev);
                if (choice == 0)      currentScreen = 4;
                else if (choice == 1) currentScreen = 7;
                else if (choice == 2) currentScreen = 2;
                else if (choice == 3) currentScreen = 3;
                else if (choice == 4) currentScreen = 6;
                else if (choice == 4) currentScreen = 6;
                else if (choice == 5) window.close();
            }
            else if (currentScreen == 4)
            {
                charSelect.handleInput(ev);
                if (charSelect.wantsBack(ev))
                    currentScreen = 0;

                int picked = charSelect.getChoice(ev);
                if (picked != -1)
                {
                    chosenCharacter = picked;
                    if (currentplayer != NULL)
                    {
                        delete currentplayer;
                        currentplayer = NULL;
                    }

                    if (chosenCharacter == 0)
                    {
                        Marco* m = new Marco(380, 300);
                        m->loadTexture("Assets/marco.png");
                        currentplayer = m;
                    }
                    else if (chosenCharacter == 1)
                    {
                        Tarma* t = new Tarma(380, 300);
                        t->loadTexture("Assets/tarma.png");
                        currentplayer = t;
                    }
                    else if (chosenCharacter == 2)
                    {
                        Eri* e = new Eri(380, 300);
                        e->loadTexture("Assets/eri.png");
                        currentplayer = e;
                    }
                    else if (chosenCharacter == 3)
                    {
                        Fio* f = new Fio(380, 300);
                        f->loadTexture("Assets/fio.png");
                        currentplayer = f;
                    }

                    player_x = 380;
                    player_y = 300;
                    cameraX = 0;
                    gravityY = 0;
                    currentScreen = 1;
                }
            }
            else if (currentScreen == 7)
            {
                survCharSelect.handleInput(ev);
                if (survCharSelect.wantsBack(ev))
                    currentScreen = 0;

                int picked = survCharSelect.getChoice(ev);
                if (picked != -1)
                {
                    if (survivalPlayer != NULL)
                    {
                        delete survivalPlayer;
                        survivalPlayer = NULL;
                    }

                    if (picked == 0)
                    {
                        Marco* m = new Marco(380, 300);
                        m->loadTexture("Assets/marco.png");
                        survivalPlayer = m;
                    }
                    else if (picked == 1)
                    {
                        Tarma* t = new Tarma(380, 300);
                        t->loadTexture("Assets/tarma.png");
                        survivalPlayer = t;
                    }
                    else if (picked == 2)
                    {
                        Eri* e = new Eri(380, 300);
                        e->loadTexture("Assets/eri.png");
                        survivalPlayer = e;
                    }
                    else if (picked == 3)
                    {
                        Fio* f = new Fio(380, 300);
                        f->loadTexture("Assets/fio.png");
                        survivalPlayer = f;
                    }

                    survivalCurrentLevel = 1;
                    survLevel1.setPlayer(survivalPlayer);
                    currentScreen = 5;
                }
            }
            else if (currentScreen == 2)
            {
                if (ev.type == Event::KeyPressed)
                    currentScreen = 0;
            }
            else if (currentScreen == 3)
            {
                if (ev.type == Event::TextEntered)
                {
                    if (ev.text.unicode == '\b')
                    {
                        if (nameLen > 0)
                        {
                            nameLen--;
                            name[nameLen] = '\0';
                        }
                    }
                    else if (ev.text.unicode >= 32 && ev.text.unicode < 128)
                    {
                        if (nameLen < 99)
                        {
                            name[nameLen] = static_cast<char>(ev.text.unicode);
                            nameLen++;
                            name[nameLen] = '\0';
                        }
                    }
                }
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Enter)
                {
                    name[0] = '\0';
                    nameLen = 0;
                    currentScreen = 0;
                }
            }
        }

        if (currentScreen == 1 && Keyboard::isKeyPressed(Keyboard::Escape))
        {
            if (currentplayer != NULL && campaignKills > 0)
                scoreboard.addScore("Player", campaignKills * 100, 0);
            campaignKills = 0;
            currentScreen = 0;
        }

        if (currentScreen == 6 && Keyboard::isKeyPressed(Keyboard::Escape))
            currentScreen = 0;
        if (currentScreen == 8 && Keyboard::isKeyPressed(Keyboard::Escape))
            currentScreen = 0;
        if ((currentScreen == 5 || currentScreen == 55 || currentScreen == 56) &&
            Keyboard::isKeyPressed(Keyboard::Escape))
        {
            if (survivalPlayer != NULL)
            {
                delete survivalPlayer;
                survivalPlayer = NULL;
            }
            survLevel1.reset();
            survLevel2.reset();
            survLevel3.reset();
            survivalCurrentLevel = 1;
            currentScreen = 0;
        }

        if (currentScreen == 1)
            bgMusic.stop();
        if (currentScreen == 0)
        {
            if (bgMusic.getStatus() != sf::Music::Playing)
                bgMusic.play();
        }

        if (currentScreen == 1 && currentplayer != NULL)
        {
            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                if (!insideVehicle)
                {
                    for (int i = 0; i < maxvehicles; i++)
                    {
                        if (flyingTaras[i] != NULL)
                        {
                            float dx = currentplayer->getX() - flyingTaras[i]->getX();

                            if (abs(dx) < 120)
                            {
                                insideVehicle = true;
                                currentVehicle = flyingTaras[i];
                                break;
                            }
                        }
                    }
                }
                else
                {
                    insideVehicle = false;

                    currentplayer->setPosition(
                        currentVehicle->getX() + 100,
                        currentVehicle->getY()
                    );

                    currentVehicle = NULL;
                }
            }
            if (!insideVehicle)
            {
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    currentplayer->moveRight();
                else if (Keyboard::isKeyPressed(Keyboard::Left))
                    currentplayer->moveLeft();
                else
                    currentplayer->stopMoving();
            }
            else
            {
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    currentVehicle->moveRight();

                if (Keyboard::isKeyPressed(Keyboard::Left))
                    currentVehicle->moveLeft();

                currentplayer->setPosition(
                    currentVehicle->getX(),
                    currentVehicle->getY() - 50
                );
            }
            if (Keyboard::isKeyPressed(Keyboard::Space))
                currentplayer->jump();

            currentplayer->applyGravity();
            currentplayer->update();

            float groundY = infiniteMap.getGroundY(
                currentplayer->getX() + currentplayer->getWidth() / 2.0f
            );
            currentplayer->landOnGround(groundY);
            world.updateProjectiles();

            if (Keyboard::isKeyPressed(Keyboard::X))
            {
                currentplayer->shoot(&world);
                if (currentplayer->getWeapon() != NULL)
                    currentplayer->getWeapon()->update();
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                currentplayer->fireHMG(&world);
            }
            if (Keyboard::isKeyPressed(Keyboard::C))
            {
                currentplayer->fireRocket(&world);
            }
            if (Keyboard::isKeyPressed(Keyboard::V))
            {
                currentplayer->fireFlame(&world);
            }
            if (Keyboard::isKeyPressed(Keyboard::B))
            {
                currentplayer->fireLaser(&world);
            }
            if (Keyboard::isKeyPressed(Keyboard::Z))
            {
                currentplayer->throwGrenade(&world);
            }

            currentplayer->updateProjectiles(groundY);
            currentplayer->updateDamageState();
            if (currentplayer->getDamageState() == STATE_DEAD)
            {
                if (leaderboard.isHighScore(scoreSystem.getScore()))
                    leaderboard.addScore(name, scoreSystem.getScore());

                currentplayer->respawn();
            }

            world.checkCollisions(currentplayer, enemies, max_enemies, dmgText, cameraX);
            if (cameraX + screen_x > nextCollectableSpawnX)
            {
                float collectGroundY = infiniteMap.getGroundY(nextCollectableSpawnX);
                collectables.spawnRandom(cameraX, screen_x, collectGroundY);
                nextCollectableSpawnX += 500.0f + (rand() % 500);
            }
            collectables.update(currentplayer);

            if (cameraX + screen_x > nextSpawnX)
            {
                int enemyType = rand() % 4;
                int batchSize = 0;
                if (enemyType == 0) batchSize = (rand() % 3) + 2;
                else                batchSize = (rand() % 2) + 1;

                for (int i = 0; i < batchSize; i++)
                {
                    for (int j = 0; j < max_enemies; j++)
                    {
                        if (enemies[j] == NULL || !enemies[j]->IsAlive())
                        {
                            if (enemies[j] != NULL)
                            {
                                delete enemies[i];
                                enemies[j] = NULL;
                            }
                            float spawnX = cameraX + screen_x + 100 + (i * 150);
                            if (enemyType == 0)
                            {
                                RebelSoldier* rs = new RebelSoldier(spawnX, 100);
                                rs->loadTexture("Assets/rebel.png");
                                enemies[j] = rs;
                            }
                            else if (enemyType == 1)
                            {
                                BazookaSoldier* bs = new BazookaSoldier(spawnX, 100);
                                bs->loadTexture("Assets/bazooka.png");
                                enemies[j] = bs;
                            }
                            else if (enemyType == 2)
                            {
                                ShieldedSoldier* ss = new ShieldedSoldier(spawnX, 100);
                                ss->loadTexture("Assets/shielded.png");
                                enemies[j] = ss;
                            }
                            else if (enemyType == 3)
                            {
                                GrenadeSoldier* gs = new GrenadeSoldier(spawnX, 100);
                                gs->loadTexture("Assets/grenade.png");
                                enemies[j] = gs;
                            }
                            break;
                        }
                    }
                }
                float randomDistance = 1000.0f + (rand() % 1000);
                nextSpawnX += randomDistance;
            }

            if (cameraX + screen_x > nextVehicleSpawnX)
            {
                int vehicleType = rand() % 5;
                float spawnX = cameraX - 100;
                int batchSize = 1;
                if (vehicleType <= 2)
                    batchSize = 2;
                for (int b = 0; b < batchSize; b++)
                {
                    for (int i = 0; i < maxvehicles; i++)
                    {
                        if (vehicleType == 0 && flyingTaras[i] == NULL)
                        {
                            FlyingTara* ft = new FlyingTara(spawnX + b * 200, 200);
                            ft->loadTexture("Assets/flying_tara.png", "Assets/grenade.png");
                            flyingTaras[i] = ft;
                            break;
                        }
                        else if (vehicleType == 1 && bradleys[i] == NULL)
                        {
                            Bradley* br = new Bradley(spawnX, 100);
                            br->loadTexture("Assets/bradley.png", "Assets/missile.png");
                            bradleys[i] = br;
                            break;
                        }
                        else if (vehicleType == 2 && enemySubs[i] == NULL)
                        {
                            EnemySub* es = new EnemySub(spawnX, 500);
                            es->loadTexture("Assets/enemy_sub.png", "Assets/rocket.png");
                            enemySubs[i] = es;
                            break;
                        }

                    }
                }
                float randomDistance = 700.0f + (rand() % 500);
                nextVehicleSpawnX += randomDistance;
            }

            for (int i = 0; i < max_enemies; i++)
            {
                if (enemies[i] != NULL && enemies[i]->IsAlive())
                {
                    float enemyGroundY = infiniteMap.getGroundY(enemies[i]->getX() + enemies[i]->getWidth() / 2.0f);
                    enemies[i]->landOnGround(enemyGroundY);
                    enemies[i]->update();
                    enemies[i]->enemyShoot(&world, currentplayer->getX(), currentplayer->getY());
                }
                if (enemies[i] != NULL && !enemies[i]->IsAlive())
                {
                    campaignKills++;

                    scoreSystem.addKillScore(
                        enemies[i]->getEnemyType(),
                        !currentplayer->isOnGround(),
                        false
                    );

                    delete enemies[i];
                    enemies[i] = NULL;
                }
            }
            for (int i = 0; i < maxvehicles; i++)
            {
                if (flyingTaras[i] != NULL)
                    flyingTaras[i]->draw(window, cameraX);

                if (bradleys[i] != NULL && bradleys[i]->isActive())
                    bradleys[i]->draw(window, cameraX);

                if (enemySubs[i] != NULL && enemySubs[i]->isActive())
                    enemySubs[i]->draw(window, cameraX);
            }
            scoreSystem.update();
            cameraX = currentplayer->getX() - screen_x / 2.0f + currentplayer->getWidth() / 2.0f;
            if (cameraX < 0) cameraX = 0;

            for (int i = 0; i < maxvehicles; i++)
            {
                if (flyingTaras[i] != NULL && flyingTaras[i]->isActive())
                {
                    if (currentVehicle != flyingTaras[i])
                    {
                        flyingTaras[i]->update();
                        flyingTaras[i]->dropGrenade(currentplayer->getX(), currentplayer->getY());
                    }
                }
                if (bradleys[i] != NULL && bradleys[i]->isActive())
                {
                    float bradleyGroundY = infiniteMap.getGroundY(bradleys[i]->getX() + 50);
                    bradleys[i]->landOnGround(bradleyGroundY);
                    bradleys[i]->approachPlayer(currentplayer->getX());
                    bradleys[i]->shoot();
                    bradleys[i]->update();
                }
                if (enemySubs[i] != NULL && enemySubs[i]->isActive())
                {
                    enemySubs[i]->fireAtPlayer(currentplayer->getX(), currentplayer->getY());
                    enemySubs[i]->update();
                }
            }
        }

        if (currentScreen == 5 && survivalPlayer != NULL)
        {
            survLevel1.update(dmgText);

            if (survLevel1.isGameOver())
            {
                scoreboard.addScore("Player", survLevel1.getKillCount() * 100, 1);

                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if (survivalPlayer != NULL)
                    {
                        delete survivalPlayer;
                        survivalPlayer = NULL;
                    }
                    Marco* m = new Marco(380, 300);
                    m->loadTexture("Assets/marco.png");
                    survivalPlayer = m;
                    survivalCurrentLevel = 1;
                    survLevel1.reset();
                    survLevel1.setPlayer(survivalPlayer);
                }
            }

            if (survLevel1.isLevelClear())
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    survLevel1.reset();
                    survivalCurrentLevel = 2;
                    survLevel2.setPlayer(survivalPlayer);
                    currentScreen = 55;
                }
            }
        }

        if (currentScreen == 55 && survivalPlayer != NULL)
        {
            survLevel2.update(dmgText);

            if (survLevel2.isGameOver())
            {
                scoreboard.addScore("Player", (survLevel1.getKillCount() + survLevel2.getKillCount()) * 100, 2);

                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if (survivalPlayer != NULL)
                    {
                        delete survivalPlayer;
                        survivalPlayer = NULL;
                    }
                    Marco* m = new Marco(380, 300);
                    m->loadTexture("Assets/marco.png");
                    survivalPlayer = m;
                    survivalCurrentLevel = 1;
                    survLevel1.reset();
                    survLevel2.reset();
                    survLevel1.setPlayer(survivalPlayer);
                    currentScreen = 5;
                }
            }

            if (survLevel2.isLevelClear())
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    survLevel2.reset();
                    survivalCurrentLevel = 3;
                    survLevel3.setPlayer(survivalPlayer);
                    currentScreen = 56;
                }
            }
        }

        if (currentScreen == 56 && survivalPlayer != NULL)
        {
            survLevel3.update(dmgText);

            if (survLevel3.isGameOver())
            {
                scoreboard.addScore("Player", (survLevel1.getKillCount() + survLevel2.getKillCount() + survLevel3.getKillCount()) * 100, 3);

                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if (survivalPlayer != NULL)
                    {
                        delete survivalPlayer;
                        survivalPlayer = NULL;
                    }
                    Marco* m = new Marco(380, 300);
                    m->loadTexture("Assets/marco.png");
                    survivalPlayer = m;
                    survivalCurrentLevel = 1;
                    survLevel1.reset();
                    survLevel2.reset();
                    survLevel3.reset();
                    survLevel1.setPlayer(survivalPlayer);
                    currentScreen = 5;
                }
            }

            if (survLevel3.isLevelClear())
            {
                scoreboard.addScore("Player", (survLevel1.getKillCount() + survLevel2.getKillCount() + survLevel3.getKillCount()) * 100, 3);

                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if (survivalPlayer != NULL)
                    {
                        delete survivalPlayer;
                        survivalPlayer = NULL;
                    }
                    survLevel1.reset();
                    survLevel2.reset();
                    survLevel3.reset();
                    survivalCurrentLevel = 1;
                    currentScreen = 0;
                }
            }
        }

        window.clear();

        if (currentScreen == 0)
        {
            menu.draw(window);
        }
        else if (currentScreen == 1)
        {
            infiniteMap.draw(window, cameraX);

            if (currentplayer != NULL)
                currentplayer->draw(window, cameraX);

            if (currentplayer->getWeapon() != NULL)
                currentplayer->getWeapon()->render(window, cameraX);

            world.draw(window, cameraX);
            collectables.draw(window, cameraX);
            currentplayer->drawBullets(window, cameraX);

            if (currentplayer->getDamageState() == STATE_INJURED)
            {
                redHue.setFillColor(sf::Color(255, 0, 0, 60));
                window.draw(redHue);
            }
            else if (currentplayer->getDamageState() == STATE_CRITICAL)
            {
                redHue.setFillColor(sf::Color(255, 0, 0, 120));
                window.draw(redHue);
            }

            char livesText[50] = "";
            sprintf_s(livesText, "Lives: %d", currentplayer->getLives());
            infoText.setPosition(20, 20);
            infoText.setCharacterSize(30);
            infoText.setString(livesText);
            window.draw(infoText);
            infoText.setPosition(150, 150);
            infoText.setCharacterSize(35);

            window.draw(dmgText);
            scoreSystem.drawPopup(window);

            for (int i = 0; i < max_enemies; i++)
            {
                if (enemies[i] != NULL && enemies[i]->IsAlive())
                    enemies[i]->draw(window, cameraX);
            }
            for (int i = 0; i < maxvehicles; i++)
            {
                if (flyingTaras[i] != NULL)
                    flyingTaras[i]->draw(window, cameraX);

                if (bradleys[i] != NULL)
                    bradleys[i]->draw(window, cameraX);

                if (enemySubs[i] != NULL)
                    enemySubs[i]->draw(window, cameraX);
            }
        }
        else if (currentScreen == 2)
        {
            infoText.setString(
                "INSTRUCTIONS\n\n"
                "Arrow Keys : Move Left / Right\n"
                "Space      : Jump\n"
                "X          : Shoot\n"
                "C          : Rocket\n"
                "V          : Flame\n"
                "B          : Laser\n"
                "Z          : Grenade\n"
                "Q          : Fire Bomb\n"
                "Escape     : Back to Menu\n\n"
                "Press any key to return..."
            );
            window.draw(infoText);
        }
        else if (currentScreen == 3)
        {
            char credits[300] = "";
            strcat_s(credits, "CREDITS\n\nGame by : ");
            strcat_s(credits, name);
            strcat_s(credits, "\nScore   : 0\nEngine  : SFML + C++\n\nType your name, Press Enter to return...");
            infoText.setString(credits);
            window.draw(infoText);
        }
        else if (currentScreen == 4)
        {
            charSelect.draw(window);
        }
        else if (currentScreen == 7)
        {
            survCharSelect.draw(window);
        }
        else if (currentScreen == 6)
        {
            scoreboard.draw(window);
        }
        else if (currentScreen == 5)
        {
            survLevel1.draw(window, dmgText);
        }
        else if (currentScreen == 55)
        {
            survLevel2.draw(window, dmgText);
        }
        else if (currentScreen == 56)
        {
            survLevel3.draw(window, dmgText);
        }
        else if (currentScreen == 8)
        {
            leaderboard.draw(window);

            infoText.setPosition(550, 750);
            infoText.setString("Press Escape to go back");
            window.draw(infoText);

            infoText.setPosition(150, 150);
        }

        window.display();
    }

    if (currentplayer != NULL)
    {
        delete currentplayer;
        currentplayer = NULL;
    }
    if (survivalPlayer != NULL)
    {
        delete survivalPlayer;
        survivalPlayer = NULL;
    }
    for (int i = 0; i < maxvehicles; i++)
    {
        if (flyingTaras[i] != NULL) { delete flyingTaras[i]; flyingTaras[i] = NULL; }
        if (bradleys[i] != NULL) { delete bradleys[i];    bradleys[i] = NULL; }
        if (enemySubs[i] != NULL) { delete enemySubs[i];   enemySubs[i] = NULL; }
    }

    return 0;
}