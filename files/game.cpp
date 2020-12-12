#include "graphics.h"
#include "config.h"
#include "game.h"

void Game::update()
{
	if (!player_initialized && graphics::getGlobalTime() > 500)
	{
		player = new Player();
		player_initialized = true;
	}

	if (player)
	{
		player->update();
	}
}

void Game::draw()
{
	// Draw background
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	// Draw player
	if (player)
	{
		player->draw();
	}
}

void Game::init()
{
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete player;
	}
}