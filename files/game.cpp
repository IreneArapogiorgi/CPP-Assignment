#include "graphics.h"
#include "obstacle.h"
#include "config.h"
#include "game.h"
#include "util.h"

void Game::updateStartScreen()
{
	// Start game if Enter is pressed
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_LEVEL;
	}

	// Start game if mouse is pressed
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed)
	{
		status = STATUS_LEVEL;
	}
}

void Game::updateLevelScreen()
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
	if (!ball_initialized && (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_S)
		|| graphics::getKeyState(graphics::SCANCODE_K) || graphics::getKeyState(graphics::SCANCODE_L)))
	{
		ball_initialized = true;
	}

	if (ball && ball_initialized)
	{
		ball->update();
	}

	// Check collision between ball and playerA
	if (playerA && checkPlayerCollision(*playerA))
	{
		// Re-direct ball
		ball->init();
		ball->update();
	}

	// Check collision between ball and playerB
	if (playerB && checkPlayerCollision(*playerB))
	{
		// Re-direct ball
		ball->init();
		ball->update();
	}

	// Check collision between ball and obstacles
	if (obstacles)
	{
		for (int i = 0; i < OBSTACLES_PER_ROW * OBSTACLE_ROWS; i++)
		{
			int index = checkObstacleCollision(*obstacles[i], i);
			if (index != -1)
			{
				// Remove collided obstacle
				removeObstacle(*obstacles[i], i);

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
			playerB->reduceLife();
			ball->setPosX(playerB->getPosX());
			ball->setPosY(65);
			ball->setBallMode(0);
			ball_initialized = false;
		}
	}

	// End game if each of the players loses
	if (playerA && playerB && playerA->getLife() == 0)
	{
		status = STATUS_END;
		loser = 1;
	}

	if (playerA && playerB && playerB->getLife() == 0)
	{
		status = STATUS_END;
		loser = 2;
	}
}

void Game::updateEndScreen()
{
	// Go to start screen if Enter is pressed
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_START;
	}

	// Go to start screen if mouse is pressed
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed)
	{
		status = STATUS_START;
	}
}

void Game::drawStartScreen()
{
	// Draw background
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "startscreen.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

void Game::drawLevelScreen()
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
		array_name = "obstacle_array" + std::to_string(i + 1);

		if (obstacle_array[array_name])
		{
			for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
				// Draw each obstacle only if it's not already destroyed
				if (obstacle_array[array_name][j]) obstacle_array[array_name][j]->draw();
			}
		}
	}
}

void Game::drawEndScreen()
{
	graphics::Brush br;
	graphics::setFont(std::string(ASSET_PATH) + "info_font.ttf");

	char info[15];
	if (loser == 2) sprintf_s(info, "PLAYER A LOST!");
	if (loser == 1) sprintf_s(info, "PLAYER B LOST!");
	graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 60, info, br);
}

// Map obstacle arrays
void Game::mapObstacles()
{
	obstacle_array.insert(std::make_pair("obstacle_array1", obstacle_array1));
	obstacle_array.insert(std::make_pair("obstacle_array2", obstacle_array2));
	obstacle_array.insert(std::make_pair("obstacle_array3", obstacle_array3));
	obstacle_array.insert(std::make_pair("obstacle_array4", obstacle_array4));
}

// Fill obstacles array with all active obstacles
void Game::setObstacles(Obstacle* obstacle)
{
	obstacles[obstacles_index++] = obstacle;
}

// Remove obstacle after collision
void Game::removeObstacle(Obstacle& obstacle, int index)
{
	for (int i = 0; i < OBSTACLE_ROWS; i++) {
		array_name = "obstacle_array" + std::to_string(i + 1);

		for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
			if (&(*obstacle_array[array_name][j]) == &obstacle) {
				delete& (*obstacle_array[array_name][j]);
				obstacle_array[array_name][j] = nullptr;
				break;
			}
		}
	}
	obstacles[index] = nullptr;
}

bool Game::checkPlayerCollision(const Player& player)
{
	if (&player && ball)
	{
		Disk player_disk = player.getCollisionHull();
		Disk ball_disk = ball->getCollisionHull();

		float dx = player_disk.cx - ball_disk.cx;
		float dy = player_disk.cy - ball_disk.cy;

		if (sqrt(dx * dx + dy * dy) < player_disk.radius + ball_disk.radius)
			return true;
		else
			return false;
	}
	return false;
}

int Game::checkObstacleCollision(const Obstacle& obstacle, int index)
{
	if (&obstacle && ball)
	{
		Disk obstacle_disk = obstacle.getCollisionHull();
		Disk ball_disk = ball->getCollisionHull();
		
		float dx = obstacle_disk.cx - ball_disk.cx;
		float dy = obstacle_disk.cy - ball_disk.cy;

		if (sqrt(dx * dx + dy * dy) < obstacle_disk.radius + ball_disk.radius)
			return index;
		else
			return -1;
	}
	return -1;
}

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_LEVEL)
	{
		updateLevelScreen();
	}
	else
	{
		updateEndScreen();
	}
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_LEVEL)
	{
		drawLevelScreen();
	}
	else
	{
		drawEndScreen();
	}
}

void Game::init()
{
	// Map obstacle arrays
	mapObstacles();

	// Create obstacles
	for (int i = 0; i < OBSTACLES_PER_ROW; i++)
	{
		obstacle_array1[i] = new Obstacle(*this, float(i * 20) + CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 - 50, 20, 20);
		setObstacles(obstacle_array1[i]);

		obstacle_array2[i] = new Obstacle(*this, float(i * 20) + CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 - 20, 20, 20);
		setObstacles(obstacle_array2[i]);

		obstacle_array3[i] = new Obstacle(*this, float(i * 20) + CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 + 10, 20, 20);
		setObstacles(obstacle_array3[i]);

		obstacle_array4[i] = new Obstacle(*this, float(i * 20) + CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 + 40, 20, 20);
		setObstacles(obstacle_array4[i]);
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

	if (ball)
	{
		delete ball;
	}

	for (int i = 0; i < OBSTACLE_ROWS; i++) {
		array_name = "obstacle_array" + std::to_string(i + 1);

		if (obstacle_array[array_name])
		{
			for (int j = 0; j < OBSTACLES_PER_ROW; j++) {
				delete obstacle_array[array_name][i];
			}
			delete[] obstacle_array[array_name];
		}
	}

	if (obstacles)
	{
		delete[] obstacles;
	}
}