#include "graphics.h"
#include "obstacle.h"
#include "config.h"
#include "game.h"

bool Game::checkCollision()
{
	return false;
}

void Game::update()
{
	if (playerA)
	{
		playerA->update();
	}

	if (playerB)
	{
		playerB->update();
	}

	// Start ball movement when playerA begins playing
	if (!ball_initialized && (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_S)))
	{
		ball_initialized = true;
	}

	if (ball && ball_initialized)
	{
		ball->update();
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
	if (obstacle_array1 && obstacle_array2 && obstacle_array3 && obstacle_array4)
	{
		for (int i = 0; i < OBSTACLES_NUM; i++)
		{
			obstacle_array1[i]->draw();
			obstacle_array2[i]->draw();
			obstacle_array3[i]->draw();
			obstacle_array4[i]->draw();
		}
	}

	// Draw ball
	if (ball)
	{
		ball->draw();
	}
}

void Game::init()
{
	// Create obstacles
	for (int i = 0; i < OBSTACLES_NUM; i++)
	{
		obstacle_array1[i] = new Obstacle(*this, float(i * 20) + CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 - 50, 20, 20);
		obstacle_array2[i] = new Obstacle(*this, float(i * 20) + CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 - 20, 20, 20);
		obstacle_array3[i] = new Obstacle(*this, float(i * 20) + CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 + 10, 20, 20);
		obstacle_array4[i] = new Obstacle(*this, float(i * 20) + CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 + 40, 20, 20);
	}

	// Initialize ball
	ball->init();
}

Game::Game()
{
	// Create players
	playerA = new Player(*this, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 30, 50, 50, graphics::SCANCODE_A, graphics::SCANCODE_S);
	playerB = new Player(*this, CANVAS_WIDTH / 2, CANVAS_HEIGHT - (CANVAS_HEIGHT - 30), 50, 50, graphics::SCANCODE_K, graphics::SCANCODE_L);

	// Create ball
	ball = new Ball(*this, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 65, 25, 25);
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

	if (obstacle_array1 && obstacle_array2 && obstacle_array3 && obstacle_array4)
	{
		for (int i = 0; i < OBSTACLES_NUM; i++)
		{
			delete obstacle_array1[i];
			delete obstacle_array2[i];
			delete obstacle_array3[i];
			delete obstacle_array4[i];
		}
		delete[] obstacle_array1;
		delete[] obstacle_array2;
		delete[] obstacle_array3;
		delete[] obstacle_array4;
	}

	if (ball)
	{
		delete ball;
	}
}