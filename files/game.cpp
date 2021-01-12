#include "game.h"

status_t Screen::status{STATUS_START};

void Game::update()
{
	switch (startscreen->getStatus()) {
		case STATUS_START:
			startscreen->update();
			break;
		case STATUS_LEVEL:
			levelscreen->update();
			break;
		case STATUS_END:
			endscreen->update();
			delete levelscreen;

			// Start new game
			this->init();
			break;
	}
}

void Game::draw()
{
	switch (startscreen->getStatus()) {
		case STATUS_START:
			startscreen->draw();
			break;
		case STATUS_LEVEL:
			levelscreen->draw();
			break;
		case STATUS_END:
			endscreen->draw();
			break;
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
	startscreen->setStatus(STATUS_START);
}

Game::~Game()
{
}