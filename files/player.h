#pragma once
#include "gameobject.h"

class Player : public GameObject
{
	graphics::scancode_t keyLeft, keyRight;
	const float speed = 10.0f;
	int life;
public:
	void update() override;
	void init() override;
	void startingPos();
	void reduceLife() { life = std::max<int>(0, life - 1); }
	int getLife() const { return life; }
	const float getSpeed() const { return speed; }
	Player(const class Game& mygame, float pos_x, float pos_y, float width, float height, 
		  graphics::scancode_t keyLeft, graphics::scancode_t keyRight, int life);
};