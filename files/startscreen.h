#pragma once
#include "screen.h"

class StartScreen : public Screen
{
public:
	void update(status_t& status) override;
	void draw() override;
	void init() override;
	StartScreen(const class Game& mygame);
};