#pragma once
#include "player.h"
#include "config.h"

class PlayerB : public Player
{
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT - (CANVAS_HEIGHT - 30);
public:
	void update() override;
	void draw() override;
	void init() override;
	PlayerB(const class Game& mygame);
	~PlayerB();
};