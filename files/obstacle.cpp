#include "graphics.h"
#include "obstacle.h"
#include "config.h"

void Obstacle::update()
{
}

void Obstacle::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "ghost.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 20, 20, br);
}

void Obstacle::init()
{
}

Obstacle::Obstacle(const Game& mygame) : GameObject(mygame)
{
}