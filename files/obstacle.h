#pragma once
#include "gameobject.h"

class Obstacle : public GameObject
{
	float l = 1;
	unsigned int life = 2;
public:
	void update() override;
	void draw() override;
	void init() override;
	void reduceLife();
	bool isAlive();
	unsigned int getLife() const { return life; }
	Obstacle(const class Game& mygame, float pos_x, float pos_y, float width, float height);
};