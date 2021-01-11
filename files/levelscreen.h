#pragma once
#include "obstacle.h"
#include "screen.h"
#include "config.h"
#include "player.h"
#include "ball.h"
#include <map>

class LevelScreen : public Screen
{
	// Keys for players' movement
	graphics::scancode_t playerA_keyL = graphics::SCANCODE_A;
	graphics::scancode_t playerA_keyR = graphics::SCANCODE_D;
	graphics::scancode_t playerB_keyL = graphics::SCANCODE_J;
	graphics::scancode_t playerB_keyR = graphics::SCANCODE_L;

	GameObject* players[2];
	Player* playerA = nullptr;
	Player* playerB = nullptr;

	Obstacle*** obstacles = new Obstacle * *[OBSTACLE_ROWS];
	float st[4][2] = { {CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 - 50}, {CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 - 20}, 
					   {CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 + 10}, {CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 + 40} };

	Ball* ball = nullptr;
	bool ball_initialized = false;

	void removeObstacle(Obstacle& obstacle);
public:
	void update(status_t& status) override;
	void draw() override;
	void init() override;
	LevelScreen(const class Game& mygame);
	~LevelScreen();
};