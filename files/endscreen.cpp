#include "endscreen.h"
#include "graphics.h"
#include "config.h"

void EndScreen::update()
{
	// Start new game if Enter is pressed
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_LEVEL;
	}
}

void EndScreen::draw()
{
	graphics::setFont(std::string(ASSET_PATH) + "screen_font.ttf");

	char gameover[10];
	sprintf_s(gameover, "GAME OVER");
	graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 70, gameover, br);

	char newgame[32];
	sprintf_s(newgame, "PRESS ENTER TO START A NEW GAME");
	graphics::drawText(CANVAS_WIDTH / 5, CANVAS_HEIGHT / 1.7f, 40, newgame, br);
}

void EndScreen::init()
{
}

EndScreen::EndScreen(const Game& mygame) : Screen(mygame)
{
}