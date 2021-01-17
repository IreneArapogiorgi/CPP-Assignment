#include "startscreen.h"

void StartScreen::update()
{
	// Show text
	br.fill_opacity += 0.003f;

	// Proceed to menu after 3 seconds
	if (getGlobalTime() > 3000)
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
	
	br.texture = string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	string str = "SPACE  BATTLES";
	drawText(CANVAS_WIDTH / 5 + 30, CANVAS_HEIGHT / 2, 80, str, br);
}

void StartScreen::init()
{
}

StartScreen::StartScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_START;
	br.fill_opacity = 0.0f;

	// Start background music
	string music = string(ASSET_PATH) + "background_sound.mp3";
	playMusic(music, 0.2, true, 0);
}