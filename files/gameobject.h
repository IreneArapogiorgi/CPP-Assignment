#pragma once
#include "graphics.h"

class GameObject
{
protected:
	const class Game& game;
	float pos_x, pos_y, width, height;
	graphics::Brush br;
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	GameObject(const class Game& mygame, float pos_x, float pos_y, float width, float height);
	~GameObject();
};