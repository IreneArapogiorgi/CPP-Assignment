#pragma once
#include "gameobject.h"

class Player : public GameObject
{
	scancode_t keyLeft, keyRight;
	const float speed = 10.0f;
	unsigned int life;
public:
	void update() override;
	void init() override;

	void startingPos();
	unsigned int getLife() const { return life; }
	const float getSpeed() const { return speed; }
	void reduceLife() { life = std::max<unsigned int>(0, life - 1); }
	Player(const class Game& mygame, float pos_x, float pos_y, float width, float height, 
		   scancode_t keyLeft, scancode_t keyRight, unsigned int life);
};