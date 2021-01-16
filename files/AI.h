#pragma once
#include "config.h"
#include "player.h"
#include "ball.h"

class AI
{
	float timer = 0.0;
	bool flag = true;
	Player* player;
	Ball* ball;
public:
	AI(Player* player, Ball* ball);
	void update();
};