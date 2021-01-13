#include "levelscreen.h"
#include "graphics.h"
#include "game.h"
#include "util.h"
#include <ctime>

void LevelScreen::update()
{
	if (playerA)
	{
		playerA->update();
	}

	if (playerB)
	{
		playerB->update();
	}

	if (ball && ball->respawn()) {
		ball->update();

		// Check collision between ball and obstacles
		for (int i = 0; i < OBSTACLE_ROWS; i++) {
			int index = ball->checkCollision(reinterpret_cast<GameObject**>(obstacles[i]), OBSTACLES_PER_ROW);

			if (index != -1)
			{
				// Play collision sound
				std::string wav = std::string(ASSET_PATH) + "collision_sound.wav";
				graphics::playSound(wav, 0.2f);

				// Reduce obstacle's life
				obstacles[i][index]->reduceLife();

				// Remove collided obstacle
				if (obstacles[i][index]->getLife() == 0)
				{
					delete obstacles[i][index];
					obstacles[i][index] = nullptr;
				}
				break;
			}
		}

		// Check collision between ball and players
		ball->checkCollision(players, 2);
	}
	else {
		playerA->startingPos();
		playerB->startingPos();
		ball->start();
	}

	// Update each player's life
	int bounds = ball->outOfbounds();

	if (bounds == 1)
	{
		if (playerB && playerB->getLife() > 0)
		{
			playerB->reduceLife();
			ball->setPosX(CANVAS_WIDTH / 2);
			ball->setPosY(65);
			ball->setKeys(playerB_keyL, playerB_keyR);
		}
	}

	if (bounds == 2)
	{
		if (playerA && playerA->getLife() > 0)
		{
			playerA->reduceLife();
			ball->setPosX(CANVAS_WIDTH / 2);
			ball->setPosY(CANVAS_HEIGHT - 65);
			ball->setKeys(playerA_keyL, playerA_keyR);
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
	if (obstacles) {
		for (int i = 0; i < OBSTACLE_ROWS; i++) {
			for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
				if (obstacles[i][j] && obstacles[i][j]->isAlive()) {
					obstacles[i][j]->draw();
				}
			}
		}
	}
}

void LevelScreen::init()
{
	// Create players
	playerA = new Player(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 30, 50, 50, playerA_keyL, playerA_keyR);
	playerB = new Player(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - (CANVAS_HEIGHT - 30), 50, 50, playerB_keyL, playerB_keyR);

	players[0] = playerA;
	players[1] = playerB;

	// Create ball
	std::srand(std::time(nullptr));
	int random_variable = std::rand() % 2;

	if (random_variable == 1)
	{
		ball = new Ball(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 65, 20, 20);
		ball->setKeys(playerA_keyL, playerA_keyR);
	}
	else {
		ball = new Ball(game, CANVAS_WIDTH / 2, 65, 20, 20);
		ball->setKeys(playerB_keyL, playerB_keyR);
	}

	// Create obstacles
	for (int i = 0; i < OBSTACLE_ROWS; i++) {
		obstacles[i] = new Obstacle * [OBSTACLES_PER_ROW];
		for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
			obstacles[i][j] = new Obstacle(game, float(j * 20) + st[i][0], st[i][1], 20, 20);
			obstacles[i][j]->init();
		}
	}
}

LevelScreen::LevelScreen(const Game& mygame) : Screen(mygame)
{
	this->init();
}

LevelScreen::~LevelScreen()
{
	// Delete players
	if (playerA)
	{
		delete playerA;
	}

	if (playerB)
	{
		delete playerB;
	}

	// Delete ball
	if (ball)
	{
		delete ball;
	}

	// Delete obstacles
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