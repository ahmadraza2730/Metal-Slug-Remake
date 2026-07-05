#pragma once
#include "Enemy.h"
class Infantry : public Enemy
{

protected:
	int minBatch;
	int maxBatch;

public:
	Infantry(float startX, float startY, int w, int h, int hp, float s, int d, int minBatch, int maxBatch) 
	: Enemy(startX, startY, w, h, hp, s, d) {
		this->minBatch = minBatch;
		this->maxBatch = maxBatch;
	}
	virtual void update() override=0;
	virtual void draw(sf::RenderWindow & window, float Camx) override=0;

	int getMinBatch() const {
		return minBatch;
	}
	int getMaxBatch() const {
		return maxBatch;
	}
	virtual ~Infantry() {}
};