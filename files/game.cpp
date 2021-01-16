#include "game.h"

status_t Screen::status{STATUS_START};

void Game::update()
{
	switch (startscreen->getStatus()) {
		case STATUS_START:
			startscreen->update();
			break;

		case STATUS_MENU:
			menuscreen->update();
			if (!menuscreen->onCharge()) {
				levelscreen->setDiff(menuscreen->diff());
				levelscreen->setLevel(menuscreen->level());
				levelscreen->setAI(menuscreen->getAI());
				levelscreen->init();
				delete menuscreen;
			}
			break;

		case STATUS_LEVEL:
			levelscreen->update();
			endscreen->setWinner(levelscreen->getWinner());
			break;

		case STATUS_END:
			endscreen->update();
			if (!endscreen->onCharge()) {
				delete startscreen;
				delete levelscreen;
				delete endscreen;

				// Start new game
				this->init();
			}
			break;

		case STATUS_ESCAPE:
			delete startscreen;
			delete levelscreen;
			delete endscreen;

			// Start new game
			this->init();
			startscreen->setStatus(STATUS_MENU);
	}
}

void Game::draw()
{
	switch (startscreen->getStatus()) {
		case STATUS_START:
			startscreen->draw();
			break;
		case STATUS_MENU:
			menuscreen->draw();
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
	startscreen = new StartScreen(*this);
	menuscreen = new MenuScreen(*this);
	levelscreen = new LevelScreen(*this);
	endscreen = new EndScreen(*this);
}

Game::Game()
{
}

Game::~Game()
{
	/*delete startscreen;
	delete menuscreen;
	delete levelscreen;
	delete endscreen;*/
}