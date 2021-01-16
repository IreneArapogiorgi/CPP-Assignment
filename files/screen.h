#pragma once
#include "graphics.h"

typedef enum { STATUS_START, STATUS_MENU, STATUS_LEVEL, STATUS_END, STATUS_ESCAPE } status_t;

class Screen
{
protected:
	const class Game& game;
	static status_t status;
	graphics::Brush br;
	status_t self;
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	status_t getStatus() { return status; }
	void setStatus(status_t st) { status = st; }
	bool onCharge() { return (self == status); }
	Screen(const class Game& mygame);
	~Screen();
};