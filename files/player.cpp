#include "player.h"

void Player::update()
{
	// Move player using given keys
	if (getKeyState(keyLeft))
	{
		pos_x -= getSpeed() * getDeltaTime() / BALL_MOVEMENT;
	}
	if (getKeyState(keyRight))
	{
		pos_x += getSpeed() * getDeltaTime() / BALL_MOVEMENT;
	}

	// Keep player within canvas borders
	if (pos_x < width / 2) pos_x = width / 2;
	if (pos_x > CANVAS_WIDTH - width / 2) pos_x = CANVAS_WIDTH - width / 2;
}

void Player::init()
{
}

void Player::startingPos()
{
	pos_x = CANVAS_WIDTH / 2;
}

Player::Player(const Game& mygame, float pos_x, float pos_y, float width, float height, scancode_t keyLeft, scancode_t keyRight, unsigned int l)
			  : GameObject(mygame, pos_x, pos_y, width, height), keyLeft(keyLeft), keyRight(keyRight), life(l)
{
	// Draw player
	br.texture = string(ASSET_PATH) + "player.png";
	br.outline_opacity = 0.0f;
}