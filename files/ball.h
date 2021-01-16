#pragma once
#include "gameobject.h"

class Ball : public GameObject
{
	graphics::scancode_t keyLeft, keyRight;
	float speed = 1.8f;
	float speedY = speed;
	float speedX = 0.0f;
	bool flag = false;

	void reflectX() { speedX *= -1; }
	void reflectY() { speedY *= -1; }
public:
	void update() override;
	void draw() override;
	void init() override;

	bool respawn() { return flag; }
	void startBall() { flag = true; }
	void setSpeed(float s) { speed = s; }
	const float getSpeedX() const { return speedX; }

	void start();
	int outOfbounds();
	int checkCollision(GameObject* objects[], int size);
	void setKeys(graphics::scancode_t keyLeft, graphics::scancode_t keyRight);
	Ball(const class Game& mygame, float pos_x, float pos_y, float width, float height);
};