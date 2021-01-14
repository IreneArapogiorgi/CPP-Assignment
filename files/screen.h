#pragma once
#include "graphics.h"

typedef enum { STATUS_START, STATUS_LEVEL, STATUS_END } status_t;

class Screen
{
protected:
	static status_t status;
	const class Game& game;
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