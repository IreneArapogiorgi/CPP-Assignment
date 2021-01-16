#pragma once
#include "screen.h"

class InfoScreen : public Screen
{
public:
	void update() override;
	void draw() override;
	void init() override;
	InfoScreen(const class Game& mygame);
};