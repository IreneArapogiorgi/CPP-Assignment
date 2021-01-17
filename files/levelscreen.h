#pragma once
#include "obstacle.h"
#include "screen.h"
#include "player.h"
#include "ball.h"
#include "AI.h"

class LevelScreen : public Screen
{
	unsigned int playerTurn = 0;
	unsigned int level = 1;
	unsigned int diff = 1;
	bool AIflag = false;
	char winner = '0';

	// Keys for players' movement
	const scancode_t playerA_keyL = SCANCODE_A;
	const scancode_t playerA_keyR = SCANCODE_D;
	const scancode_t playerB_keyL = SCANCODE_J;
	const scancode_t playerB_keyR = SCANCODE_L;

	GameObject* players[2];
	Player* playerA = nullptr;
	Player* playerB = nullptr;

	Obstacle*** obstacles = new Obstacle * *[OBSTACLE_ROWS];

	// Position of each series of obstacles
	const float st[4][2] = { {CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 - 50}, {CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 - 20},
						   {CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 + 10}, {CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 + 40} };

	Ball* ball = nullptr;
	AI* ai = nullptr;
public:
	void setAI(bool ai) { AIflag = ai; }
	char getWinner() const { return winner; }
	void setLevel(unsigned int l) { level = l; }
	void setDiff(unsigned int d) { diff = d; }

	void update() override;
	void draw() override;
	void init() override;
	LevelScreen(const class Game& mygame);
	~LevelScreen();
};