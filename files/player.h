#pragma once
#include "gameobject.h"

class Player : public GameObject
{
	const float speed = 10.0f;
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	const float getSpeed() { return speed; }
	Player(const class Game& mygame);
};