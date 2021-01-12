#include "config.h"
#include "ball.h"
#include "game.h"
#include "util.h"
#include "math.h"
#include <random>
#include <iostream>
#include <algorithm>

void Ball::update()
{
	float future_pos_x = pos_x + direction_x * speed;
	float future_pos_y = pos_y + direction_y * speed;
	bool play_collision_sound = false;

	if ((future_pos_x + radius) >= CANVAS_WIDTH) {
		math::vec2 dir{ direction_x, direction_y };
		math::vec2 normal = { -1.0f, 0.0f };
		math::vec2 reflection = math::reflect(dir, normal);
		direction_x = reflection.x;
		direction_y = reflection.y;
		play_collision_sound = true;
	}
	else if ((future_pos_x - radius) <= 0.0f) {
		math::vec2 dir{ direction_x, direction_y };
		math::vec2 normal = { 1.0f, 0.0f };
		math::vec2 reflection = math::reflect(dir, normal);
		direction_x = reflection.x;
		direction_y = reflection.y;
		play_collision_sound = true;
	}

	if ((future_pos_y + radius) >= CANVAS_HEIGHT) {
		ball_outofbounds = 2;
	}
	else if ((future_pos_y - radius) <= 0.0f) {
		ball_outofbounds = 1;
	}

	if (play_collision_sound) {
		std::string wav = std::string(ASSET_PATH) + "ball_sound.wav";
		graphics::playSound(wav, 1.0f);
	}

	pos_x += direction_x * speed;
	pos_y += direction_y * speed;
}

void Ball::draw()
{
	// Draw ball
	br.texture = std::string(ASSET_PATH) + "ball.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, width, height, br);

	// Draw collision hull on debug mode
	if (game.getDebugMode())
	{
		br.outline_opacity = 0.7f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}

void Ball::init()
{
	std::random_device seed;
	std::default_random_engine generator(seed());
	std::uniform_real_distribution<float> distribution(-1.0, 1.0);

	direction_x = distribution(generator);
	direction_y = distribution(generator);

	// Normalize
	float length = std::sqrt(direction_x * direction_x + direction_y * direction_y);
	direction_x /= length;
	direction_y /= length;
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

					if (Cos < cos(PI / 4)) {
						reflectY();
					}
					else {
						reflectX();
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

Disk Ball::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = width / 2;
	return disk;
}

Ball::Ball(const Game& mygame, float pos_x, float pos_y, float width, float height) : GameObject(mygame, pos_x, pos_y, width, height)
{
	radius = (width * width) / (8 * height) + height / 2;
}