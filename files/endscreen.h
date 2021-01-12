#pragma once
#include "screen.h"

class EndScreen : public Screen
{
public:
	void update() override;
	void draw() override;
	void init() override;
	EndScreen(const class Game& mygame);
};