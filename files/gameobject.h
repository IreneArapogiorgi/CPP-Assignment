#pragma once
#include "graphics.h"
#include "config.h"

using namespace graphics;
using namespace std;

class GameObject
{
protected:
	const class Game& game;
	float pos_x, pos_y, width, height;
	Brush br;
public:
	virtual void draw();
	virtual void update() = 0;
	virtual void init() = 0;

	float getWidth() const { return width; }
	float getHeight() const { return height; }

	float getPosX() const { return pos_x; }
	float getPosY() const { return pos_y; }

	void setPosX(float x) { pos_x = x; }
	void setPosY(float y) { pos_y = y; }
	GameObject(const class Game& mygame, float pos_x, float pos_y, float width, float height);
	virtual ~GameObject();
};