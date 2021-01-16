#include "menuscreen.h"
#include "graphics.h"
#include "config.h"
#include "game.h"

void MenuScreen::update()
{
	graphics::getMouseState(mouse);
	bPoint = 0;

	for (int i = 1; i < 4; i++) {
		if (mouse.cur_pos_y * RATEH >= MENUSCREEN_HEIGHT * (i + 2.5) - 25 && mouse.cur_pos_y * RATEH <= MENUSCREEN_HEIGHT * (i + 2.5) + 5) {
			if (mouse.cur_pos_x * RATEW >= MENUSCREEN_WIDTH - 60 && mouse.cur_pos_x * RATEW <= MENUSCREEN_WIDTH - 60 + 100) {
				if (mouse.button_left_pressed) {
					status = STATUS_LEVEL;
				}
				bPoint = i;
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if (mouse.cur_pos_y * RATEH >= MENUSCREEN_HEIGHT * 7.5 - 25 && mouse.cur_pos_y * RATEH <= MENUSCREEN_HEIGHT * 7.5 + 5) {
			if (mouse.cur_pos_x * RATEW >= MENUSCREEN_WIDTH - 120 + (i * 65) && mouse.cur_pos_x * RATEW <= MENUSCREEN_WIDTH + 30 + (i * 65)) {
				if (mouse.button_left_pressed) {
					dPoint = i;
				}
			}
		}
	}

	if (mouse.cur_pos_y * RATEH >= MENUSCREEN_HEIGHT * 9.1 - 25 && mouse.cur_pos_y * RATEH <= MENUSCREEN_HEIGHT * 9.1 + 5) {
		if (mouse.cur_pos_x * RATEW >= CANVAS_WIDTH / 3 && mouse.cur_pos_x * RATEW <= CANVAS_WIDTH / 3 + 315) {
			if (mouse.button_left_pressed) {
				AI = !AI;
			}
		}
	}
}

void MenuScreen::draw()
{
	// Draw background
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	graphics::setFont(std::string(ASSET_PATH) + "screen_font.ttf");

	std::string str = "CHOOSE LEVEL";
	graphics::drawText(CANVAS_WIDTH / 3, MENUSCREEN_HEIGHT * 1.7, 50, str, br);

	// Change LEVEL 1 option's color on hover
	if (bPoint == 1) {
		brush(0.1, 1);
	}

	str = "LEVEL 1";
	graphics::drawText(MENUSCREEN_WIDTH - 60, MENUSCREEN_HEIGHT * 3.5, 30, str, br);

	// White color of LEVEL 1 option
	if (bPoint == 1) {
		brush(1, 1);
	}

	// Change LEVEL 2 option's color on hover
	if (bPoint == 2) {
		brush(0.1, 1);
	}

	str = "LEVEL 2";
	graphics::drawText(MENUSCREEN_WIDTH - 60, MENUSCREEN_HEIGHT * 4.5, 30, str, br);

	// White color of LEVEL 2 option
	if (bPoint == 2) {
		brush(1, 1);
	}

	// Change LEVEL 3 option's color on hover
	if (bPoint == 3) {
		brush(0.1, 1);
	}

	str = "LEVEL 3";
	graphics::drawText(MENUSCREEN_WIDTH - 60, MENUSCREEN_HEIGHT * 5.5, 30, str, br);

	// White color of LEVEL 3 option
	if (bPoint == 3) {
		brush(1, 1);
	}

	// Change EASY option's color on click
	if (dPoint == 0) {
		brush(0.2, 2);
	}

	str = "EASY";
	graphics::drawText(MENUSCREEN_WIDTH - 120, MENUSCREEN_HEIGHT * 7.5, 30, str, br);

	// White color of EASY option
	if (dPoint == 0) {
		brush(1, 2);
	}

	// Change HARD option's color on click
	if (dPoint == 1) {
		brush(0.2, 2);
	}

	str = "HARD";
	graphics::drawText(MENUSCREEN_WIDTH + 30, MENUSCREEN_HEIGHT * 7.5, 30, str, br);

	// White color of HARD option
	if (dPoint == 1) {
		brush(1, 2);
	}

	// Change PLAY AGAINST COMPUTER option's color on click
	if (AI) {
		brush(0.2, 2);
	}

	str = "PLAY AGAINST COMPUTER";
	graphics::drawText(CANVAS_WIDTH / 3, MENUSCREEN_HEIGHT * 9.2, 30, str, br);

	if (AI) {
		brush(1, 0);
	}
}

void MenuScreen::init()
{
}

MenuScreen::MenuScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_MENU;
}