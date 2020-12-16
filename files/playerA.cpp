#include "graphics.h"
#include "playerA.h"
#include "config.h"
#include "game.h"

void PlayerA::update()
{
	// Move player using keys A, S
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= getSpeed() * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		pos_x += getSpeed() * graphics::getDeltaTime() / 10.0f;
	}

	// Keep player within canvas borders
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}

void PlayerA::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "ghost.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 50, 50, br);
}

void PlayerA::init()
{
}

PlayerA::PlayerA(const Game& mygame) : Player(mygame)
{
}

PlayerA::~PlayerA()
{
}