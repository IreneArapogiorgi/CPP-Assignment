#include "startscreen.h"
#include "graphics.h"
#include "config.h"
#include "game.h"

void StartScreen::update()
{
	// Start game if Enter is pressed
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
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

	char startgame[23];
	sprintf_s(startgame, "PRESS ENTER TO PROCEED");
	graphics::drawText(CANVAS_WIDTH / 4.3f, STARTSCREEN_HEIGHT * 3, 50, startgame, br);

	// Change color of text
	brush(0.7, 0);
	brush(0.7, 1);
	brush(0.7, 2);

	std::string str = "PLAYER  1  MOVES  WITH  A  AND  D";
	graphics::drawText(STARTSCREEN_WIDTH + 40, STARTSCREEN_HEIGHT * 5.2, 20, str, br);

	str = "PLAYER  2  MOVES  WITH  J  AND  L";
	graphics::drawText(STARTSCREEN_WIDTH + 40, STARTSCREEN_HEIGHT * 6.2, 20, str, br);

	str = "PRESS  SPACE  TO  THROW  THE  BALL";
	graphics::drawText(STARTSCREEN_WIDTH + 30, STARTSCREEN_HEIGHT * 7.2, 20, str, br);

	str = "PRESS  Q  TO  RETURN  TO  THE  MENU";
	graphics::drawText(STARTSCREEN_WIDTH + 30, STARTSCREEN_HEIGHT * 8.2, 20, str, br);
}

void StartScreen::init()
{
}

StartScreen::StartScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_START;
}