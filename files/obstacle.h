#pragma once
#include "gameobject.h"

class Obstacle : public GameObject
{
	float l = 1.0f;
	unsigned int life;
public:
	void update() override;
	void init() override;

	bool isAlive();
	unsigned int getLife() const { return life; }
	void reduceLife() { life = max<unsigned int>(0, life - 1); }
	Obstacle(const class Game& mygame, float pos_x, float pos_y, float width, float height, unsigned int life);
};