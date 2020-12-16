#pragma once
#include "obstacle.h"
#include "playerA.h"
#include "playerB.h"
#include "config.h"

class Game
{
	PlayerA* playerA = nullptr;
	bool playerA_initialized = false;

	PlayerB* playerB = nullptr;
	bool playerB_initialized = false;

	Obstacle** obstacles = new Obstacle * [OBSTACLES_NUM];
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();
};