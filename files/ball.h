#pragma once
#include "gameobject.h"

class Ball : public GameObject
{
	graphics::scancode_t keyLeft, keyRight;
	const float speed = 2.0f;
	float speedY = 5.0f;
	float speedX = 0.0f;
	bool flag = false;
public:
	void update() override;
	void draw() override;
	void init() override;

	bool respawn() { return flag; }
	void reflectX() { speedX *= -1; }
	void reflectY() { speedY *= -1; }
	const float getSpeed() const { return speed; }

	void start();
	int outOfbounds();
	int checkCollision(GameObject* objects[], int size);
	void setKeys(graphics::scancode_t keyLeft, graphics::scancode_t keyRight);
	Ball(const class Game& mygame, float pos_x, float pos_y, float width, float height);
};