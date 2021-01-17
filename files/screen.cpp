#include "screen.h"

Screen::Screen(const Game& mygame) : game(mygame)
{
	// Set standard font
	setFont(string(ASSET_PATH) + "screen_font.ttf");
}

Screen::~Screen()
{
}