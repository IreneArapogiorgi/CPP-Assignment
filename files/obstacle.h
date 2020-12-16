#pragma once
#include "gameobject.h"

class Obstacle : public GameObject
{
	float pos_x, pos_y;
public:
	void update() override;
	void draw() override;
	void init() override;
	void setX(float x) { pos_x = x; }
	void setY(float y) { pos_y = y; }
	Obstacle(const class Game& mygame);
};