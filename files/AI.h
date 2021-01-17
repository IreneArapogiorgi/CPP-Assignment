#pragma once
#include "player.h"
#include "ball.h"

class AI
{
	const class Game& game;
	float timer = 0.0f;
	bool flag = true;

	Player* player;
	Ball* ball;
public:
	void update();
	AI(const class Game& mygame, Player* player, Ball* ball);
	~AI();
};