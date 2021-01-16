#pragma once
#include "startscreen.h"
#include "levelscreen.h"
#include "menuscreen.h"
#include "infoscreen.h"
#include "endscreen.h"

class Game
{
	StartScreen* startscreen = nullptr;
	MenuScreen* menuscreen = nullptr;
	InfoScreen* infoscreen = nullptr;
	LevelScreen* levelscreen = nullptr;
	EndScreen* endscreen = nullptr;
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();
};