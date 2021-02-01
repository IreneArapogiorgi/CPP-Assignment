#include "menuscreen.h"

void MenuScreen::update()
{
	getMouseState(mouse);
	float pos_x = windowToCanvasX(mouse.cur_pos_x);
	float pos_y = windowToCanvasY(mouse.cur_pos_y);

	bPoint = 0;

	// Level options
	for (int i = 1; i < 4; i++) {
		if (pos_y >= MENUSCREEN_HEIGHT * (i + 2.5) - 25 && pos_y <= MENUSCREEN_HEIGHT * (i + 2.5) + 5) {
			if (pos_x >= MENUSCREEN_WIDTH - 60 && pos_x <= MENUSCREEN_WIDTH + 40) {
				if (mouse.button_left_pressed) {
					status = STATUS_INFO;
				}
				bPoint = i;
			}
		}
	}

	// Difficulty options
	for (int i = 0; i < 2; i++) {
		if (pos_y >= MENUSCREEN_HEIGHT * 7.5 - 25 && pos_y <= MENUSCREEN_HEIGHT * 7.5 + 5) {
			if (pos_x >= MENUSCREEN_WIDTH - 120 + (i * 65) && pos_x <= MENUSCREEN_WIDTH + 30 + (i * 65)) {
				if (mouse.button_left_pressed) {
					dPoint = i;
				}
			}
		}
	}

	// AI option
	if (pos_y >= MENUSCREEN_HEIGHT * 9 - 25 && pos_y <= MENUSCREEN_HEIGHT * 9 + 5) {
		if (pos_x >= CANVAS_WIDTH / 3 && pos_x <= CANVAS_WIDTH / 3 + 315) {
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

	br.texture = string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	string str = "CHOOSE LEVEL";
	drawText(CANVAS_WIDTH / 3, MENUSCREEN_HEIGHT * 1.7, 50, str, br);

	// Change LEVEL 1 option's color on hover
	if (bPoint == 1) {
		brush(0.1, 1);
	}

	str = "LEVEL 1";
	drawText(MENUSCREEN_WIDTH - 60, MENUSCREEN_HEIGHT * 3.5, 30, str, br);

	// White color of LEVEL 1 option
	if (bPoint == 1) {
		brush(1, 1);
	}

	// Change LEVEL 2 option's color on hover
	if (bPoint == 2) {
		brush(0.1, 1);
	}

	str = "LEVEL 2";
	drawText(MENUSCREEN_WIDTH - 60, MENUSCREEN_HEIGHT * 4.5, 30, str, br);

	// White color of LEVEL 2 option
	if (bPoint == 2) {
		brush(1, 1);
	}

	// Change LEVEL 3 option's color on hover
	if (bPoint == 3) {
		brush(0.1, 1);
	}

	str = "LEVEL 3";
	drawText(MENUSCREEN_WIDTH - 60, MENUSCREEN_HEIGHT * 5.5, 30, str, br);

	// White color of LEVEL 3 option
	if (bPoint == 3) {
		brush(1, 1);
	}

	// Change EASY option's color on click
	if (dPoint == 0) {
		brush(0.2, 2);
	}

	str = "EASY";
	drawText(MENUSCREEN_WIDTH - 120, MENUSCREEN_HEIGHT * 7.5, 30, str, br);

	// White color of EASY option
	if (dPoint == 0) {
		brush(1, 2);
	}

	// Change HARD option's color on click
	if (dPoint == 1) {
		brush(0.2, 2);
	}

	str = "HARD";
	drawText(MENUSCREEN_WIDTH + 30, MENUSCREEN_HEIGHT * 7.5, 30, str, br);

	// White color of HARD option
	if (dPoint == 1) {
		brush(1, 2);
	}

	// Change PLAY AGAINST COMPUTER option's color on click
	if (AI) {
		brush(0.2, 2);
	}

	str = "PLAY AGAINST COMPUTER";
	drawText(CANVAS_WIDTH / 3, MENUSCREEN_HEIGHT * 9, 30, str, br);

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