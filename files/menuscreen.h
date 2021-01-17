#pragma once
#include "screen.h"

class MenuScreen : public Screen
{
	MouseState mouse;
	unsigned int bPoint = 0;
	unsigned int dPoint = 0;
	bool AI = false;

	// Add color of text
	void brush(float i, int j) { br.fill_color[j] = i; }
public:
	void update() override;
	void draw() override;
	void init() override;

	bool getAI() const { return AI; }
	unsigned int diff() const { return dPoint; }
	unsigned int level() const { return bPoint; }
	MenuScreen(const class Game& mygame);
};