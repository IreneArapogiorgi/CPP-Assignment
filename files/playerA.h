#pragma once
#include "player.h"
#include "config.h"

class PlayerA : public Player
{
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT - 30;
public:
	void update() override;
	void draw() override;
	void init() override;
	PlayerA(const class Game& mygame);
	~PlayerA();
};