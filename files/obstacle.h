#pragma once
#include "gameobject.h"

class Obstacle : public GameObject
{
	float l = 1;
	int life;
public:
	void update() override;
	void init() override;
	void reduceLife() { life = std::max<int>(0, life - 1); }
	bool isAlive();
	int getLife() const { return life; }
	Obstacle(const class Game& mygame, float pos_x, float pos_y, float width, float height, int life);
};