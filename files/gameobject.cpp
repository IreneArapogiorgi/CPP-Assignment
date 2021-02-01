#include "gameobject.h"

void GameObject::draw()
{
	// Draw game object
	drawRect(pos_x, pos_y, width, height, br);
}

GameObject::GameObject(const Game& mygame, float x, float y, float width, float height) : game(mygame), 
					   pos_x(x), pos_y(y), width(width), height(height)
{
}

GameObject::~GameObject()
{
}