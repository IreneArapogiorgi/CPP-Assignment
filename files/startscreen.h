#pragma once
#include "screen.h"

class StartScreen : public Screen
{
	// Add color of text
	void brush(float i, int j) { br.fill_color[j] = i; }
public:
	void update() override;
	void draw() override;
	void init() override;
	StartScreen(const class Game& mygame);
};