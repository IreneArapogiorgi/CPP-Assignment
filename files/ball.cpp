#include "config.h"
#include "ball.h"
#include "game.h"
#include "math.h"
#include <random>
#include <iostream>
#include <algorithm>

void Ball::update()
{
	int u = 1;
	if (speedX > -0.1 && speedX < 0.1) {
		speedX *= 2;
		if (speedX == 0) {
			std::default_random_engine generator;
			std::uniform_real_distribution<> distribution(-0.1, 0.1);
			speedX = distribution(generator);
		}
		if (speedY < 0) u = -1;
		speedY = sqrt(pow(speed, 2) - pow(speedX, 2)) * u;
	}
	else if (speedY > -0.1 && speedY < 0.1) {
		speedY *= 2;
		if (speedY == 0) {
			std::default_random_engine generator;
			std::uniform_real_distribution<> distribution(-0.1, 0.1);
			speedY = distribution(generator);
		}
		if (speedX < 0) u = -1;
		speedX = sqrt(pow(speed, 2) - pow(speedY, 2)) * u;
	}

	bool play_sound = false;

	if (flag == true) {
		if (pos_x >= CANVAS_WIDTH || pos_x <= 0) {
			if (pos_x < -1.0) {
				pos_x = 0.1 + width / 2;
			}
			if (pos_x > CANVAS_WIDTH + 1.0) {
				pos_x = CANVAS_WIDTH - width / 2 - 0.1;
			}
			reflectX();
			play_sound = true;
		}
		pos_x += speedX;
		pos_y += speedY;
	}

	if (play_sound) {
		std::string wav = std::string(ASSET_PATH) + "ball_sound.wav";
		graphics::playSound(wav, 1.0f);
	}
}

void Ball::draw()
{
	// Add fade effect when ball is moving
	if (flag)
	{
		br.fill_opacity = 0.2;
		drawRect(pos_x + (speedX * -4), pos_y + (speedY * -4), width, height, br);
		br.fill_opacity = 0.3;
		drawRect(pos_x + (speedX * -2), pos_y + (speedY * -2), width, height, br);
	}

	br.fill_opacity = 1.0;
	drawRect(pos_x, pos_y, width, height, br);
}

void Ball::init()
{
}

void Ball::start()
{
	if (graphics::getKeyState(keyLeft))
	{
		flag = true;
		speedX -= graphics::getDeltaTime() / 1000;
		if (speedX <= -speed) { speedX = -speed + 0.1; }
	}

	if (graphics::getKeyState(keyRight))
	{
		flag = true;
		speedX += graphics::getDeltaTime() / 1000;
		if (speedX >= speed) { speedX = speed - 0.1; }
	}

	speedY = sqrt(pow(speed, 2) - pow(speedX, 2));
	if (pos_y > 100) reflectY();
}

int Ball::outOfbounds()
{
	if (pos_y >= CANVAS_HEIGHT + 10) {
		flag = false;
		speedX = 0;
		speedY = speed;
		return 1;
	}

	if (pos_y <= -10) {
		flag = false;
		speedX = 0;
		speedY = speed;
		return 2;
	}
	return 0;
}

// Check collision between ball and given objects
int Ball::checkCollision(GameObject* objects[], int size)
{
	GameObject* temp;

	for (int i = 0; i < size; i++) {
		if (objects[i] != nullptr) {
			temp = objects[i];

			float w = temp->getWidth();
			float h = temp->getHeight();
			float deltaX = pos_x - std::max(temp->getPosX() - width / 2, std::min(pos_x, temp->getPosX() + width / 2));
			float deltaY = pos_y - std::max(temp->getPosY() - height / 2, std::min(pos_y, temp->getPosY() + height / 2));

			if ((deltaX * deltaX + deltaY * deltaY) < (height * height / 4)) {
				float Cos;

				if (deltaX == 0 && deltaY == 0) {
					reflectX();
					reflectY();
				}
				else if (!(deltaX == 0 || deltaY == 0)) {
					int yp = 1;
					int xp = 1;

					if (speedX < 0) xp = -1;
					if (speedY < 0) yp = -1;

					Cos = deltaY / (sqrt(deltaX * deltaX) + sqrt(deltaY * deltaY));

					if (Cos < 0) Cos *= -1;

					speedX = speed * Cos * xp;
					speedY = sqrt(pow(speed, 2) - pow(speedX, 2)) * yp;

					if (deltaX * speedX < 0 && deltaY * speedY < 0) {
						if (Cos < cos(PI / 4)) {
							reflectY();
						}
						else {
							reflectX();
						}
					}
					else {
						if (Cos > cos(PI / 4)) {
							if (deltaX * speedX < 0) {
								reflectX();
							}
							else {
								reflectY();
							}
						}
					}
				}
				else if (deltaY == 0) {
					reflectX();
				}
				else {
					reflectY();
				}

				float disx;
				float disy;

				disx = temp->getPosX() - pos_x;
				disy = temp->getPosY() - pos_y;

				if (disx < 0) disx *= -1;
				if (disy < 0) disy *= -1;

				if (disx < w / 2 + width / 2 && disy < h / 2 + height / 2) {
					disx -= w / 2 + width / 2;
					disy -= h / 2 + height / 2;

					if (disx < disy) {
						if (temp->getPosY() < pos_y) disy *= -1;
						pos_y += disy;
					}
					else {
						if (temp->getPosX() < pos_x) disx *= -1;
						pos_x += disx;
					}
				}
				return i;
			}
		}
	}
	return -1;
}

void Ball::setKeys(graphics::scancode_t keyLeft, graphics::scancode_t keyRight)
{
	this->keyLeft = keyLeft;
	this->keyRight = keyRight;
}

Ball::Ball(const Game& mygame, float pos_x, float pos_y, float width, float height) : GameObject(mygame, pos_x, pos_y, width, height)
{
	// Draw ball
	br.texture = std::string(ASSET_PATH) + "ball.png";
	br.outline_opacity = 0.0f;
}