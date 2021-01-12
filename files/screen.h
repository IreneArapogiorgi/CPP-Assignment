#pragma once
#include "graphics.h"
#include "util.h"

class Screen
{
protected:
	const class Game& game;
	static status_t status;
	unsigned int loser = 0;
	graphics::Brush br;
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	status_t getStatus() { return status; }
	void setStatus(status_t st) { status = st; }
	Screen(const class Game& mygame);
	~Screen();
};