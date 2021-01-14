#pragma once
#include "startscreen.h"
#include "levelscreen.h"
#include "endscreen.h"

class Game
{
	StartScreen* startscreen = nullptr;
	LevelScreen* levelscreen = nullptr;
	EndScreen* endscreen = nullptr;
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();
};