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
	float getWidth() { return width; }
	float getHeight() { return height; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	void setPosX(float x) { pos_x = x; }
	void setPosY(float y) { pos_y = y; }
	GameObject(const class Game& mygame, float pos_x, float pos_y, float width, float height);
	~GameObject();
};