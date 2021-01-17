#include "screen.h"

Screen::Screen(const Game& mygame) : game(mygame)
{
	// Draw standard background
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	setFont(string(ASSET_PATH) + "screen_font.ttf");
}

Screen::~Screen()
{
}