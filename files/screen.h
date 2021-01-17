#pragma once
#include "graphics.h"
#include "config.h"

typedef enum { STATUS_START, STATUS_MENU, STATUS_INFO, STATUS_LEVEL, STATUS_END, STATUS_ESCAPE } status_t;

using namespace graphics;
using namespace std;

class Screen
{
protected:
	const class Game& game;
	static status_t status;
	status_t self;
	Brush br;
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;

	bool onCharge() { return (self == status); }
	void setStatus(status_t st) { status = st; }
	status_t getStatus() const { return status; }
	Screen(const class Game& mygame);
	~Screen();
};