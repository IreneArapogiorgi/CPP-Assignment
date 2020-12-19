#pragma once
#include "gameobject.h"

class Obstacle : public GameObject
{
public:
	void update() override;
	void draw() override;
	void init() override;
	Obstacle(const class Game& mygame, float pos_x, float pos_y, float width, float height);
};