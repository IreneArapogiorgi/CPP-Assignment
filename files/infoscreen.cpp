#include "infoscreen.h"

void InfoScreen::update()
{
	// Fade out text
	br.fill_opacity -= 0.0025f;

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
	setFont(std::string(ASSET_PATH) + "screen_font.ttf");

	string str = "PLAYER  1  MOVES  WITH  A  AND  D";
	drawText(INFOSCREEN_WIDTH + 40, INFOSCREEN_HEIGHT * 3.5, 30, str, br);

	str = "PLAYER  2  MOVES  WITH  J  AND  L";
	drawText(INFOSCREEN_WIDTH + 40, INFOSCREEN_HEIGHT * 4.5, 30, str, br);

	str = "PRESS  SPACE  TO  THROW  THE  BALL";
	drawText(INFOSCREEN_WIDTH + 26, INFOSCREEN_HEIGHT * 5.5, 30, str, br);

	str = "PRESS  Q  TO  RETURN  TO  THE  MENU";
	drawText(INFOSCREEN_WIDTH + 28, INFOSCREEN_HEIGHT * 6.5, 30, str, br);
}

void InfoScreen::init()
{
}

InfoScreen::InfoScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_INFO;
	br.fill_opacity = 1.0f;
}
