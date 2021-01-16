#pragma once
#include "obstacle.h"
#include "screen.h"
#include "config.h"
#include "player.h"
#include "ball.h"
#include "AI.h"

class LevelScreen : public Screen
{
	bool AIflag = false;
	int playerTurn = 0;
	char winner = '0';
	int level = 1;
	int diff = 1;

	// Keys for players' movement
	graphics::scancode_t playerA_keyL = graphics::SCANCODE_A;
	graphics::scancode_t playerA_keyR = graphics::SCANCODE_D;
	graphics::scancode_t playerB_keyL = graphics::SCANCODE_J;
	graphics::scancode_t playerB_keyR = graphics::SCANCODE_L;

	GameObject* players[2];
	Player* playerA = nullptr;
	Player* playerB = nullptr;

	Obstacle*** obstacles = new Obstacle * *[OBSTACLE_ROWS];

	// Position of each series of obstacles
	float st[4][2] = { {CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 - 50}, {CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 - 20}, 
					   {CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 + 10}, {CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 + 40} };

	Ball* ball = nullptr;
	AI* ai = nullptr;
public:
	void setAI(bool ai) { AIflag = ai; }
	char getWinner() { return winner; }
	void setLevel(int l) { level = l; }
	void setDiff(int d) { diff = d; }

	void update() override;
	void draw() override;
	void init() override;
	LevelScreen(const class Game& mygame);
	~LevelScreen();
};