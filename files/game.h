#pragma once
#include "startscreen.h"
#include "levelscreen.h"
#include "endscreen.h"

class Game
{
	bool debug_mode = false;

	StartScreen* startscreen = nullptr;
	LevelScreen* levelscreen = nullptr;
	EndScreen* endscreen = nullptr;
public:
	void update();
	void draw();
	void init();
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	Game();
	~Game();
};