#pragma once
#include "gameobject.h"

class Obstacle : public GameObject, public Collidable
{
	unsigned int life = 2;
	unsigned int l = 1.0 / life;
public:
	void update() override;
	void draw() override;
	void init() override;
	bool isAlive();
	Disk getCollisionHull() const override;
	Obstacle(const class Game& mygame, float pos_x, float pos_y, float width, float height);
};