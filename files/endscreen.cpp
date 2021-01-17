#include "endscreen.h"

void EndScreen::update()
{
	// Proceed to start screen if Enter is pressed
	if (getKeyState(SCANCODE_RETURN))
	{
		status = STATUS_MENU;
	}
}

void EndScreen::draw()
{
	setFont(string(ASSET_PATH) + "screen_font.ttf");

	char winner[16];
	sprintf_s(winner, "PLAYER  %c  WON", this->winner);
	drawText(CANVAS_WIDTH / 4 + 35, CANVAS_HEIGHT / 2.2f, 70, winner, br);

	string str = "PRESS  ENTER  TO  START  A  NEW  GAME";
	drawText(CANVAS_WIDTH / 5 - 15, CANVAS_HEIGHT / 1.6f, 40, str, br);
}

void EndScreen::init()
{
}

EndScreen::EndScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_END;
}