#include "obstacle.h"
#include "config.h"
#include "game.h"

void Obstacle::update()
{
}

void Obstacle::draw()
{
	// Draw obstacle
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

void Obstacle::init()
{
}

bool Obstacle::isAlive()
{
	if (life == 0) return false;
	return true;
}

Disk Obstacle::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = width / 2;
	return disk;
}

Obstacle::Obstacle(const Game& mygame, float pos_x, float pos_y, float width, float height) : GameObject(mygame, pos_x, pos_y, width, height)
{
}