#pragma once

class GameObject
{
	const class Game& game;
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	GameObject(const class Game& mygame);
};