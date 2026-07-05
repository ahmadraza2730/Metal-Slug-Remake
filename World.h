#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Camera.h"
#include "Entity.h"
#include "InfiniteMap.h"
#include "Projectile.h"
#include "BallisticProjectile.h"
#include "Player.h"
#include "Enemy.h"

class World
{
private:
	static const int maxEntities = 100;

	Entity* entities[maxEntities];
	int entityCount;

	Camera camera;
	InfiniteMap* infiniteMap;

	static const int maxProjectiles = 1000;
	Projectile* projectiles[maxProjectiles];
	int projectileCount;

	int screenwidth;
	int screenheight;

public:
	World(int sw, int sh) : camera(sw, sh)
	{
		screenwidth = sw;
		screenheight = sh;

		entityCount = 0;
		infiniteMap = NULL;
		for (int i = 0;i < maxEntities; i++)
		{
			entities[i] = NULL;
		}

		projectileCount = 0;
		for (int i = 0; i < maxProjectiles; i++)
		{
			projectiles[i] = NULL;
		}

	}
	void setMap(InfiniteMap* map)
	{
		infiniteMap = map;
	}
	void addEntity(Entity* e)
	{
		if (entityCount < maxEntities)
		{
			entities[entityCount] = e;
			entityCount++;
		}
	}
	void remdead()
	{
		for (int i = 0; i < entityCount; i++)
		{
			if (entities[i] != NULL && !entities[i]->IsAlive())
			{
				delete entities[i];
				entities[i] = NULL;
			}
		}
	}
	void spawnProjectile(Projectile* p)
	{
		if (projectileCount < maxProjectiles)
		{
			projectiles[projectileCount] = p;
			projectileCount++;
		}
	}
	void update(float tarx, float tary)
	{
		camera.follow(tarx, tary);
		for (int i = 0; i < entityCount; i++)
		{
			if (entities[i] != NULL && entities[i]->IsAlive())
			{
				entities[i]->update(); 
			}
		}

		for (int i = 0; i < projectileCount; i++)
		{
			if (projectiles[i] != NULL)
			{
				projectiles[i]->update();
				if (!projectiles[i]->isActive())
				{
					delete projectiles[i];
					projectiles[i] = NULL;
				}
			}
		}
	}
	
	void draw(sf::RenderWindow& window, float camX)
	{
		
		for (int i = 0;i < entityCount;i++)
		{
			if (entities[i] != NULL && entities[i]->IsAlive())
			{
				entities[i]->draw(window, camX);
			}
		}
		for (int i = 0; i < projectileCount; i++)
		{
			if (projectiles[i] != NULL)
			{
				projectiles[i]->draw(window, camX);
			}
		}
	}
	float getGroundY(float pixelX)
	{
		if (infiniteMap != NULL)
		{
			return infiniteMap->getGroundY(pixelX);
		}
		else
		{
			return 0;
		}
	}



	Camera& getCamera()
	{
		return camera;
	}
	int getEntityCount()
	{
		return entityCount;
	}
	int getProjectileCount()
	{
		return projectileCount;
	}
	Projectile* getProjectile(int index)
	{
		if (index < 0 || index >= projectileCount) return NULL;
		return projectiles[index];
	}

	void updateProjectiles()
	{
		for (int i = 0; i < projectileCount; i++)
		{
			if (projectiles[i] != NULL)
			{

				BallisticProjectile* bp = dynamic_cast<BallisticProjectile*>(projectiles[i]);
				if (bp != NULL) {
					bp->setGroundY(getGroundY(bp->getX()));
				}


				projectiles[i]->update();
				if (!projectiles[i]->isActive())
				{
					delete projectiles[i];
					projectiles[i] = NULL;
				}
			}
		}
	}
	void checkCollisions(Player* player, Enemy** enemies, int maxEnemies, sf::Text& dmgText, float camX)
	{
		for (int i = 0; i < projectileCount; i++)
		{
			if (projectiles[i] == NULL || !projectiles[i]->isActive()) continue;

			sf::FloatRect pBounds = projectiles[i]->getBounds();

			if (projectiles[i]->isFromPlayer())
			{
				for (int j = 0; j < maxEnemies; j++)
				{
					if (enemies[j] == NULL || !enemies[j]->IsAlive()) continue;

					sf::FloatRect eBounds(
						enemies[j]->getX(), enemies[j]->getY(),
						static_cast<float>(enemies[j]->getWidth()),
						static_cast<float>(enemies[j]->getHeight()));

					if (pBounds.intersects(eBounds))
					{
						enemies[j]->takeDamage(projectiles[i]->getDamage());
						projectiles[i]->deactivate();

						char dmgBuf[20];
						sprintf_s(dmgBuf, "-%d", projectiles[i]->getDamage());
						dmgText.setString(dmgBuf);
						dmgText.setFillColor(sf::Color::Red);
						dmgText.setPosition(enemies[j]->getX() - camX, enemies[j]->getY() - 20);
					}
				}
			}
			else
			{
				sf::FloatRect playerBounds(
					player->getX(), player->getY(),
					static_cast<float>(player->getWidth()),
					static_cast<float>(player->getHeight()));

				if (pBounds.intersects(playerBounds))
				{
					player->takeDamage(projectiles[i]->getDamage());
					projectiles[i]->deactivate();

					dmgText.setString("OUCH!");
					dmgText.setFillColor(sf::Color::Yellow);
					dmgText.setPosition(player->getX() - camX, player->getY() - 20);
				}
			}
		}
	}

	~World()
	{
		for (int i = 0; i < entityCount; i++)
		{
			if (entities[i] != NULL)
			{
				delete entities[i];
				entities[i] = NULL;
			}
		}
		for (int i = 0; i < projectileCount; i++)
		{
			if (projectiles[i] != NULL)
			{
				delete projectiles[i];
				projectiles[i] = NULL;
			}
		}
	}
};