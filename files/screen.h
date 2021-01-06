#pragma once
#include "graphics.h"
#include "util.h"

class Screen
{
protected:
	const class Game& game;
	unsigned int loser = 0;
	graphics::Brush br;
public:
	virtual void update(status_t& status) = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	Screen(const class Game& mygame);
	~Screen();
};