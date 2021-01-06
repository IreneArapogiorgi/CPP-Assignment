#pragma once
#include "obstacle.h"
#include "screen.h"
#include "config.h"
#include "player.h"
#include "ball.h"
#include <map>

class LevelScreen : public Screen
{
	Player* playerA = nullptr;
	Player* playerB = nullptr;

	// Keys for players' movement
	graphics::scancode_t playerA_keyL = graphics::SCANCODE_A;
	graphics::scancode_t playerA_keyR = graphics::SCANCODE_D;
	graphics::scancode_t playerB_keyL = graphics::SCANCODE_J;
	graphics::scancode_t playerB_keyR = graphics::SCANCODE_L;

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

	std::string array_name;
	std::map<std::string, Obstacle**> obstacle_array;
	void mapObstacles();

	void setObstacles(Obstacle* obstacle);
	void removeObstacle(Obstacle& obstacle, int index);
	bool checkPlayerCollision(const Player& player);
	int checkObstacleCollision(const Obstacle& obstacle, int index);
public:
	void update(status_t& status) override;
	void draw() override;
	void init() override;
	LevelScreen(const class Game& mygame);
	~LevelScreen();
};