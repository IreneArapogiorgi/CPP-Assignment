#pragma once
#include "gameobject.h"

class Player : public GameObject, public Collidable
{
	graphics::scancode_t keyLeft, keyRight;
	const float speed = 10.0f;
public:
	void update() override;
	void draw() override;
	void init() override;
	const float getSpeed() { return speed; }
	Disk getCollisionHull() const override;
	Player(const class Game& mygame, float pos_x, float pos_y, float width, float height, graphics::scancode_t keyLeft, graphics::scancode_t keyRight);
};