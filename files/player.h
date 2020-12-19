#pragma once
#include "gameobject.h"

class Player : public GameObject
{
	graphics::scancode_t keyLeft, keyRight;
	const float speed = 10.0f;
public:
	void update() override;
	void draw() override;
	void init() override;
	const float getSpeed() { return speed; }
	Player(const class Game& mygame, float pos_x, float pos_y, float width, float height, graphics::scancode_t keyLeft, graphics::scancode_t keyRight);
};