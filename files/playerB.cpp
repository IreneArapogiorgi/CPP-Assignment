#include "graphics.h"
#include "playerB.h"
#include "config.h"
#include "game.h"

void PlayerB::update()
{
	// Move player using keys K, L
	if (graphics::getKeyState(graphics::SCANCODE_K))
	{
		pos_x -= getSpeed() * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_L))
	{
		pos_x += getSpeed() * graphics::getDeltaTime() / 10.0f;
	}

	// Keep player within canvas borders
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}

void PlayerB::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "ghost.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 50, 50, br);
}

void PlayerB::init()
{
}

PlayerB::PlayerB(const Game& mygame) : Player(mygame)
{
}

PlayerB::~PlayerB()
{
}