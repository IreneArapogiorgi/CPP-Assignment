#pragma once
#include "gameobject.h"

class Ball : public GameObject
{
	scancode_t keyLeft, keyRight;
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

	void startBall() { flag = true; }
	bool respawn() const { return flag; }
	void setSpeed(float s) { speed = s; }
	float getSpeedX() const { return speedX; }

	void start();
	int outOfbounds();
	int checkCollision(GameObject* objects[], int size);
	void setKeys(scancode_t keyLeft, scancode_t keyRight);
	Ball(const class Game& mygame, float pos_x, float pos_y, float width, float height);
};