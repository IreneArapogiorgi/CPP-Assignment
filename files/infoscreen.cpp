#include "infoscreen.h"

void InfoScreen::update()
{
	// Fade out text
	br.fill_opacity -= 0.0035f;

	// Start game after text is faded out completely
	if (br.fill_opacity < 0.0f)
	{
		status = STATUS_LEVEL;
	}
}

void InfoScreen::draw()
{
	// Draw background
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	br.texture = string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	string str = "PLAYER  1  MOVES  WITH  A  AND  D";
	drawText(INFOSCREEN_WIDTH + 40, INFOSCREEN_HEIGHT * 4, 30, str, br);

	str = "PLAYER  2  MOVES  WITH  J  AND  L";
	drawText(INFOSCREEN_WIDTH + 40, INFOSCREEN_HEIGHT * 5.2, 30, str, br);

	str = "PRESS  Q  TO  RETURN  TO  THE  MENU";
	drawText(INFOSCREEN_WIDTH + 28, INFOSCREEN_HEIGHT * 6.4, 30, str, br);
}

void InfoScreen::init()
{
}

InfoScreen::InfoScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_INFO;
	br.fill_opacity = 1.0f;
}
