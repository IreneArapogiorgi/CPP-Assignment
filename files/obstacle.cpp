#include "obstacle.h"
#include "config.h"

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
}

Obstacle::Obstacle(const Game& mygame, float pos_x, float pos_y, float width, float height) : GameObject(mygame, pos_x, pos_y, width, height)
{
}