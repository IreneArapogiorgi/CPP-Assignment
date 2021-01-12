#include "startscreen.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"

void StartScreen::update()
{
	// Start game if Enter is pressed
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_LEVEL;
	}

	/* Start game if mouse is pressed
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed)
	{
		status = STATUS_LEVEL;
	}*/
}

void StartScreen::draw()
{
	// Draw background
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::setFont(std::string(ASSET_PATH) + "screen_font.ttf");

	char startgame[21];
	sprintf_s(startgame, "PRESS ENTER TO START");
	graphics::drawText(CANVAS_WIDTH / 4.5f, CANVAS_HEIGHT / 2, 60, startgame, br);
}

void StartScreen::init()
{
}

StartScreen::StartScreen(const Game& mygame) : Screen(mygame)
{
}