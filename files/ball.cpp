#include "ball.h"
#include <random>

void Ball::update()
{
	int u = 1;

	// Avoid straight direction of ball
	if (speedX > -0.1 * speed && speedX < 0.1 * speed) {
		speedX *= 2;
		// Avoid horizontal ball movement
		if (speedX == 0) {
			random_device rd;
			mt19937 mt(rd());
			uniform_real_distribution<double> dist(-0.1, 0.1);
			speedX = (float)dist(mt);
		}
		if (speedY < 0) u = -1;
		speedY = sqrt(pow(speed, 2) - pow(speedX, 2)) * u;
	}
	else if (speedY > -0.1 * speed && speedY < 0.1 * speed) {
		speedY *= 2;
		// Avoid vertical ball movement
		if (speedY == 0) {
			random_device rd;
			mt19937 mt(rd());
			uniform_real_distribution<double> dist(-0.1, 0.1);
			speedY = (float)dist(mt);
		}
		if (speedX < 0) u = -1;
		speedX = sqrt(pow(speed, 2) - pow(speedY, 2)) * u;
	}

	bool play_sound = false;

	// Re-direct ball when hitting canvas borders
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

	// Play sound when ball hits canvas borders
	if (play_sound) {
		string sound = string(ASSET_PATH) + "ball_sound.wav";
		playSound(sound, 1.0f);
	}
}

void Ball::draw()
{
	// Add blurred illusion when ball is moving
	if (flag)
	{
		br.fill_opacity = 0.2;
		drawRect(pos_x + (speedX * -4), pos_y + (speedY * -4), width, height, br);
		br.fill_opacity = 0.3;
		drawRect(pos_x + (speedX * -2), pos_y + (speedY * -2), width, height, br);
	}

	// Draw ball
	br.fill_opacity = 1.0;
	drawRect(pos_x, pos_y, width, height, br);
}

void Ball::init()
{
}

void Ball::start()
{
	// Player chooses direction of the launching ball by key pressed
	if (getKeyState(keyLeft))
	{
		flag = true;
		speedX -= getDeltaTime() / 1000;
		if (speedX <= -speed) { speedX = -speed + 0.1; }
	}

	if (getKeyState(keyRight))
	{
		flag = true;
		speedX += getDeltaTime() / 1000;
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

	for (int i = 0; i < size; ++i) {
		if (objects[i] != nullptr) {
			temp = objects[i];

			float w = temp->getWidth();
			float h = temp->getHeight();
			float deltaX = pos_x - max(temp->getPosX() - w / 2, min(pos_x, temp->getPosX() + w / 2));
			float deltaY = pos_y - max(temp->getPosY() - h / 2, min(pos_y, temp->getPosY() + h / 2));

			if ((deltaX * deltaX + deltaY * deltaY) < (height * height / 4)) {
				float Cos;

				if (deltaX == 0 && deltaY == 0) {
					reflectX();
					reflectY();
				}
				// If true, ball hits on corner
				else if (!(deltaX == 0 || deltaY == 0)) {
					int yp = 1;
					int xp = 1;

					// Keep speed direction
					if (speedX < 0) xp = -1;
					if (speedY < 0) yp = -1;

					Cos = deltaY / (sqrt(deltaX * deltaX) + sqrt(deltaY * deltaY));

					// We want the angle being positive
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
				// If deltaY == 0, ball rests on a vertical surface
				else if (deltaY == 0) {
					reflectX();
				}
				// If deltaX == 0, ball rests on a horizontal surface
				else {
					reflectY();
				}

				float disx;
				float disy;

				// If ball is found inside another game object, place it in the nearest place outside of it
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

void Ball::setKeys(scancode_t keyLeft, scancode_t keyRight)
{
	this->keyLeft = keyLeft;
	this->keyRight = keyRight;
}

Ball::Ball(const Game& mygame, float pos_x, float pos_y, float width, float height) : GameObject(mygame, pos_x, pos_y, width, height)
{
	// Draw ball
	br.texture = string(ASSET_PATH) + "ball.png";
	br.outline_opacity = 0.0f;
}