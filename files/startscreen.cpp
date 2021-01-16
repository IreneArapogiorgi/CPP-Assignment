#include "startscreen.h"
#include "graphics.h"
#include "config.h"
#include "game.h"

void StartScreen::update()
{
	// Show text
	br.fill_opacity += 0.003f;

	// Proceed to menu after approximately 4 seconds
	if (graphics::getGlobalTime() > 4000)
	{
		status = STATUS_MENU;
	}
}

void StartScreen::draw()
{
	// Draw background
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::setFont(std::string(ASSET_PATH) + "screen_font.ttf");

	char startgame[28];
	sprintf_s(startgame, "WELCOME  TO  GHOST  HUNTING");
	graphics::drawText(CANVAS_WIDTH / 5, CANVAS_HEIGHT / 2, 50, startgame, br);
}

void StartScreen::init()
{
}

StartScreen::StartScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_START;
	br.fill_opacity = 0.0f;
}