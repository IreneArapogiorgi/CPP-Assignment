#pragma once
#include "screen.h"

class EndScreen : public Screen
{
	char winner = '0';
public:
	void update() override;
	void draw() override;
	void init() override;
	void setWinner(char w) { winner = w; }
	EndScreen(const class Game& mygame);
};