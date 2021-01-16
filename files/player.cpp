#include "player.h"
#include "config.h"
#include "game.h"

void Player::update()
{
	// Move player using given keys
	if (graphics::getKeyState(keyLeft))
	{
		pos_x -= getSpeed() * graphics::getDeltaTime() / BALL_MOVEMENT;
	}
	if (graphics::getKeyState(keyRight))
	{
		pos_x += getSpeed() * graphics::getDeltaTime() / BALL_MOVEMENT;
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

Player::Player(const Game& mygame, float pos_x, float pos_y, float width, float height, graphics::scancode_t keyLeft, graphics::scancode_t keyRight, int l)
			  : GameObject(mygame, pos_x, pos_y, width, height), keyLeft(keyLeft), keyRight(keyRight), life(l)
{
	// Draw player
	br.texture = std::string(ASSET_PATH) + "ghost.png";
	br.outline_opacity = 0.0f;
}