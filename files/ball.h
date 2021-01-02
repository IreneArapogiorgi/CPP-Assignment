#pragma once
#include "gameobject.h"

class Ball : public GameObject, public Collidable
{
	float direction_x = 1.0f;
	float direction_y = 0.0f;
	const float speed = 2.0f;
	unsigned int ball_outofbounds = 0;
	float radius;
public:
	void update() override;
	void draw() override;
	void init() override;
	const float getSpeed() const { return speed; }
	void setBallMode(int mode) { ball_outofbounds = mode; }
	int getBallMode() const { return ball_outofbounds; }
	Disk getCollisionHull() const override;
	Ball(const class Game& mygame, float pos_x, float pos_y, float width, float height);
};