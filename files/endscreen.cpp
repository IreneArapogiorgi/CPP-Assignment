#include "endscreen.h"
#include "graphics.h"
#include "config.h"

void EndScreen::update()
{
	// Re-locate to start screen if Enter is pressed
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_MENU;
	}
}

void EndScreen::draw()
{
	graphics::setFont(std::string(ASSET_PATH) + "screen_font.ttf");

	std::string gameover("PLAYER  ");
	gameover += winner;
	gameover += "  WON";
	graphics::drawText(CANVAS_WIDTH / 4 + 35, CANVAS_HEIGHT / 2.2f, 70, gameover, br);

	char newgame[32];
	sprintf_s(newgame, "PRESS ENTER TO START A NEW GAME");
	graphics::drawText(CANVAS_WIDTH / 5, CANVAS_HEIGHT / 1.6f, 40, newgame, br);
}

void EndScreen::init()
{
}

EndScreen::EndScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_END;
}