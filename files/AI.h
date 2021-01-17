#pragma once
#include "player.h"
#include "ball.h"

class AI
{
	const class Game& game;
	unsigned int diff = 2;
	float timer = 0.0f;
	bool flag = true;

	Player* player;
	Ball* ball;
public:
	void update();
	void setDiff(unsigned int diff);
	AI(const class Game& mygame, Player* player, Ball* ball);
	~AI();
};