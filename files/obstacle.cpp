#include "obstacle.h"

void Obstacle::update()
{
}

void Obstacle::init()
{
	l = 1.0 / (float)life;
}

bool Obstacle::isAlive()
{
	br.fill_opacity = l * life;
	if (life == 0) return false;
	return true;
}

Obstacle::Obstacle(const Game& mygame, float pos_x, float pos_y, float width, float height, unsigned int l)
				  : GameObject(mygame, pos_x, pos_y, width, height), life(l)
{
	// Draw obstacle
	br.texture = string(ASSET_PATH) + "obstacle.png";
	br.outline_opacity = 0.0f;
}