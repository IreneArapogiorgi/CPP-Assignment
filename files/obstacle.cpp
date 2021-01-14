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
}

void Obstacle::init()
{
	l = 1.0 / life;
}

void Obstacle::reduceLife()
{
	life = std::max<unsigned int>(0, life - 1);
}

bool Obstacle::isAlive()
{
	br.fill_opacity = l * life;
	if (life == 0) return false;
	return true;
}

Obstacle::Obstacle(const Game& mygame, float pos_x, float pos_y, float width, float height) : GameObject(mygame, pos_x, pos_y, width, height)
{
}