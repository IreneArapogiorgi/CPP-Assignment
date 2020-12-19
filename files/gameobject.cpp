#include "gameobject.h"

GameObject::GameObject(const Game& mygame, float x, float y, float width, float height) : game(mygame), 
					   pos_x(x), pos_y(y), width(width), height(height)
{
}

GameObject::~GameObject()
{
}