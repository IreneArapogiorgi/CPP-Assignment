#pragma once
#include "gameobject.h"

class Ball : public GameObject, public Collidable
{
	float direction_x = 1.0f;
	float direction_y = 0.0f;
	const float speed = 2.0f;
	float radius;
public:
	void update() override;
	void draw() override;
	void init() override;
	const float getSpeed() { return speed; }
	Disk getCollisionHull() const override;
	Ball(const class Game& mygame, float pos_x, float pos_y, float width, float height);
};