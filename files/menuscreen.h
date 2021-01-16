#pragma once
#include "screen.h"

class MenuScreen : public Screen
{
	graphics::MouseState mouse;
	bool AI = false;
	int bPoint = 0;
	int dPoint = 0;

	// Add color of text
	void brush(float i, int j) { br.fill_color[j] = i; }
public:
	void update() override;
	void draw() override;
	void init() override;

	bool getAI() { return AI; }
	int diff() { return dPoint; }
	int level() { return bPoint; }
	MenuScreen(const class Game& mygame);
};