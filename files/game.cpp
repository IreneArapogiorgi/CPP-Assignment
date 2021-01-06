#include "game.h"

void Game::update()
{
	if (status == STATUS_START)
	{
		startscreen->update(status);
	}
	else if (status == STATUS_LEVEL)
	{
		levelscreen->update(status);
	}
	else
	{
		endscreen->update(status);
		//levelscreen->~LevelScreen();

		// Start new game
		this->init();
	}
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		startscreen->draw();
	}
	else if (status == STATUS_LEVEL)
	{
		levelscreen->draw();
	}
	else
	{
		endscreen->draw();
	}
}

void Game::init()
{
	// Create screens
	levelscreen = new LevelScreen(*this);
	endscreen = new EndScreen(*this);
}

Game::Game()
{
	// Create start screen
	startscreen = new StartScreen(*this);
	status = STATUS_START;
}

Game::~Game()
{
}