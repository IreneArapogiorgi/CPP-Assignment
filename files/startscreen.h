#pragma once
#include "screen.h"

class StartScreen : public Screen
{
public:
	void update() override;
	void draw() override;
	void init() override;
	StartScreen(const class Game& mygame);
};