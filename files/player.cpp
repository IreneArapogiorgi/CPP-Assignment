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
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}

void Player::draw()
{
	// Draw player
	br.texture = std::string(ASSET_PATH) + "ghost.png";
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

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = width / 2;
	return disk;
}

Player::Player(const Game& mygame, float pos_x, float pos_y, float width, float height, graphics::scancode_t keyLeft, graphics::scancode_t keyRight)
			  : GameObject(mygame, pos_x, pos_y, width, height), keyLeft(keyLeft), keyRight(keyRight)
{
}