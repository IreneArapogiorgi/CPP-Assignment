#pragma once
#include "obstacle.h"
#include "player.h"

class Game
{
	Player* playerA = nullptr;
	bool playerA_initialized = false;

	Player* playerB = nullptr;
	bool playerB_initialized = false;

	Obstacle** obstacle_array1 = new Obstacle * [OBSTACLES_NUM];
	Obstacle** obstacle_array2 = new Obstacle * [OBSTACLES_NUM];
	Obstacle** obstacle_array3 = new Obstacle * [OBSTACLES_NUM];
	Obstacle** obstacle_array4 = new Obstacle * [OBSTACLES_NUM];
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();
};