#pragma once
#include "obstacle.h"
#include "player.h"
#include "ball.h"

class Game
{
	bool debug_mode = false;

	Player* playerA = nullptr;
	Player* playerB = nullptr;

	// Obstacles array stores all obstacles created
	Obstacle** obstacles = new Obstacle * [OBSTACLES_PER_ROW * OBSTACLE_ROWS];
	int obstacles_index = 0;

	// Each obstacle_array stores a row of obstacles
	Obstacle** obstacle_array1 = new Obstacle * [OBSTACLES_PER_ROW];
	Obstacle** obstacle_array2 = new Obstacle * [OBSTACLES_PER_ROW];
	Obstacle** obstacle_array3 = new Obstacle * [OBSTACLES_PER_ROW];
	Obstacle** obstacle_array4 = new Obstacle * [OBSTACLES_PER_ROW];

	Ball* ball = nullptr;
	bool ball_initialized = false;

	void setObstacles(Obstacle* obstacle);
	void removeObstacle(Obstacle& obstacle, int index);
	bool checkPlayerCollision(const Player& player);
	int checkObstacleCollision(const Obstacle& obstacle, int index);
public:
	void update();
	void draw();
	void init();
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	Game();
	~Game();
};