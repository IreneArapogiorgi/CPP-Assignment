#include "levelscreen.h"
#include "graphics.h"
#include "config.h"
#include "game.h"
#include "util.h"

// Remove obstacle after collision
void LevelScreen::removeObstacle(Obstacle& obstacle)
{
	for (int i = 0; i < OBSTACLE_ROWS; i++) {
		for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
			if (&(*obstacles[i][j]) == &obstacle) {
				delete& (*obstacles[i][j]);
				obstacles[i][j] = nullptr;
				break;
			}
		}
	}
}

void LevelScreen::initializeBall(graphics::scancode_t keyL, graphics::scancode_t keyR)
{
	if (graphics::getKeyState(keyL) || graphics::getKeyState(keyR))
	{
		ball_initialized = true;
	}
}

void LevelScreen::update(status_t& status)
{
	if (playerA)
	{
		playerA->update();
	}

	if (playerB)
	{
		playerB->update();
	}

	// Start ball movement
	if (!ball_initialized)
	{
		if (loser == 0 && (graphics::getKeyState(playerA_keyL) || graphics::getKeyState(playerA_keyR)))
		{
			ball_initialized = true;
		}
		if (loser == 1) { initializeBall(playerA_keyL, playerA_keyR); }
		if (loser == 2) { initializeBall(playerB_keyL, playerB_keyR); }
	}

	if (ball && ball_initialized)
	{
		ball->update();
	}

	// Check collision between ball and players
	if (playerA && playerB)
	{
		if (ball->checkCollision(players, 2) != -1)
		{
			// Re-direct ball
			ball->init();
			ball->update();
		}
	}

	// Check collision between ball and obstacles
	if (obstacles)
	{
		for (int i = 0; i < OBSTACLE_ROWS; i++) {
			int index = ball->checkCollision(reinterpret_cast<GameObject**>(obstacles[i]), OBSTACLES_PER_ROW);

			if (index != -1)
			{
				// Reduce obstacle's life
				obstacles[i][index]->reduceLife();

				// Remove collided obstacle
				if (obstacles[i][index]->getLife() == 0)
				{
					removeObstacle(*obstacles[i][index]);
				}

				// Re-direct ball
				ball->init();
				ball->update();
				break;
			}
		}
	}

	// Update each player's life
	if (ball && ball->getBallMode() == 1)
	{
		if (playerA && playerA->getLife() > 0)
		{
			loser = 1;
			playerA->reduceLife();
			ball->setPosX(playerA->getPosX());
			ball->setPosY(CANVAS_HEIGHT - 65);
			ball->setBallMode(0);
			ball_initialized = false;
		}
	}

	if (ball && ball->getBallMode() == 2)
	{
		if (playerB && playerB->getLife() > 0)
		{
			loser = 2;
			playerB->reduceLife();
			ball->setPosX(playerB->getPosX());
			ball->setPosY(65);
			ball->setBallMode(0);
			ball_initialized = false;
		}
	}

	// End game if each of the players loses
	if (playerA && playerB && (playerA->getLife() == 0 || playerB->getLife() == 0))
	{
		status = STATUS_END;
	}
}

void LevelScreen::draw()
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

	// Display UI info
	if (playerA && playerB)
	{
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::setFont(std::string(ASSET_PATH) + "info_font.ttf");

		char info[10];
		sprintf_s(info, "Life: %d", playerA->getLife());
		graphics::drawText(INFOTEXT_POSX, INFOTEXT_POSY, INFOTEXT_SIZE, info, br);

		sprintf_s(info, "Life: %d", playerB->getLife());
		graphics::drawText(INFOTEXT_POSX, CANVAS_HEIGHT - INFOTEXT_POSY, INFOTEXT_SIZE, info, br);
	}

	// Draw ball
	if (ball)
	{
		ball->draw();
	}

	// Draw obstacles
	for (int i = 0; i < OBSTACLE_ROWS; i++) {
		for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
			if (obstacles[i][j]) {
				if (obstacles[i][j]->isAlive())
				{
					obstacles[i][j]->draw();
				}
			}
		}
	}
}

void LevelScreen::init()
{
	// Create obstacles
	for (int i = 0; i < OBSTACLE_ROWS; i++) {
		obstacles[i] = new Obstacle * [OBSTACLES_PER_ROW];
		for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
			obstacles[i][j] = new Obstacle(game, float(j * 20) + st[i][0], st[i][1], 20, 20);
			obstacles[i][j]->init();
		}
	}

	// Initialize ball
	ball->init();
}

LevelScreen::LevelScreen(const Game& mygame) : Screen(mygame)
{
	// Create players
	playerA = new Player(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 30, 50, 50, playerA_keyL, playerA_keyR);
	playerB = new Player(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - (CANVAS_HEIGHT - 30), 50, 50, playerB_keyL, playerB_keyR);

	players[0] = playerA;
	players[1] = playerB;

	// Create ball
	ball = new Ball(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 65, 25, 25);

	this->init();
}

LevelScreen::~LevelScreen()
{
	if (playerA)
	{
		delete playerA;
	}

	if (playerB)
	{
		delete playerB;
	}

	if (ball)
	{
		delete ball;
	}

	for (int i = 0; i < OBSTACLE_ROWS; i++) {
		for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
			if (obstacles[i][j])
			{
				delete obstacles[i][j];
			}
		}
	}

	if (obstacles)
	{
		delete[] obstacles;
	}
}