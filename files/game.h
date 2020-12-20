#pragma once
#include "obstacle.h"
#include "player.h"

class Game
{
	bool debug_mode = false;

	Player* playerA = nullptr;
	bool playerA_initialized = false;

	Player* playerB = nullptr;
	bool playerB_initialized = false;

	Obstacle** obstacle_array1 = new Obstacle * [OBSTACLES_NUM];
	Obstacle** obstacle_array2 = new Obstacle * [OBSTACLES_NUM];
	Obstacle** obstacle_array3 = new Obstacle * [OBSTACLES_NUM];
	Obstacle** obstacle_array4 = new Obstacle * [OBSTACLES_NUM];

	bool checkCollision();
public:
	void update();
	void draw();
	void init();
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	Game();
	~Game();
};