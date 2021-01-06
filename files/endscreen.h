#pragma once
#include "screen.h"

class EndScreen : public Screen
{
public:
	void update(status_t& status) override;
	void draw() override;
	void init() override;
	EndScreen(const class Game& mygame);
};