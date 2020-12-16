#include "graphics.h"
#include "obstacle.h"
#include "config.h"
#include "game.h"

void Game::update()
{
	if (!playerA_initialized && !playerB_initialized && obstacles && graphics::getGlobalTime() > 500)
	{
		playerA = new PlayerA(*this);
		playerA_initialized = true;

		playerB = new PlayerB(*this);
		playerB_initialized = true;
	}

	if (playerA)
	{
		playerA->update();
	}

	if (playerB)
	{
		playerB->update();
	}
}

void Game::draw()
{
	// Draw background
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::setWindowBackground(br);

	// Draw players
	if (playerA && playerB)
	{
		playerA->draw();
		playerB->draw();
	}

	// Draw obstacles
	if (obstacles)
	{
		for (int i = 0; i < OBSTACLES_NUM; i++)
		{
			obstacles[i]->draw();
		}
	}
}

void Game::init()
{
	// Initialize obstacles
	for (int i = 0; i < OBSTACLES_NUM; i++)
	{
		obstacles[i] = new Obstacle(*this);
	}

	int count = 0;
	for (int i = 0; i < 25; i++)
	{
		count++;
		obstacles[i]->setX(count * 20 + CANVAS_WIDTH / 4);
		obstacles[i]->setY(CANVAS_HEIGHT / 2);
	}

	count = 0;
	for (int i = 25; i < 46; i++)
	{
		count++;
		obstacles[i]->setX(count * 20 + CANVAS_WIDTH / 3.5);
		obstacles[i]->setY(CANVAS_HEIGHT / 2 + 20);
	}

	count = 0;
	for (int i = 46; i < 67; i++)
	{
		count++;
		obstacles[i]->setX(count * 20 + CANVAS_WIDTH / 3.5);
		obstacles[i]->setY(CANVAS_HEIGHT / 2 - 20);
	}
}

Game::Game()
{
}

Game::~Game()
{
	if (playerA)
	{
		delete playerA;
	}

	if (playerB)
	{
		delete playerB;
	}

	if (obstacles)
	{
		for (int i = 0; i < OBSTACLES_NUM; i++)
		{
			delete obstacles[i];
		}
		delete[] obstacles;
	}
}