#include "levelscreen.h"
#include "graphics.h"
#include "config.h"
#include "game.h"
#include "util.h"

// Map obstacle arrays
void LevelScreen::mapObstacles()
{
	obstacle_array.insert(std::make_pair("obstacle_array1", obstacle_array1));
	obstacle_array.insert(std::make_pair("obstacle_array2", obstacle_array2));
	obstacle_array.insert(std::make_pair("obstacle_array3", obstacle_array3));
	obstacle_array.insert(std::make_pair("obstacle_array4", obstacle_array4));
}

// Fill obstacles array with all active obstacles
void LevelScreen::setObstacles(Obstacle* obstacle)
{
	obstacles[obstacles_index++] = obstacle;
}

// Remove obstacle after collision
void LevelScreen::removeObstacle(Obstacle& obstacle, int index)
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

bool LevelScreen::checkPlayerCollision(const Player& player)
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

int LevelScreen::checkObstacleCollision(const Obstacle& obstacle, int index)
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

	// Start ball movement when playerA begins playing
	if (!ball_initialized && (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_D)
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

void LevelScreen::init()
{
	// Map obstacle arrays
	mapObstacles();

	// Create obstacles
	for (int i = 0; i < OBSTACLES_PER_ROW; i++)
	{
		obstacle_array1[i] = new Obstacle(game, float(i * 20) + CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 - 50, 20, 20);
		setObstacles(obstacle_array1[i]);

		obstacle_array2[i] = new Obstacle(game, float(i * 20) + CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 - 20, 20, 20);
		setObstacles(obstacle_array2[i]);

		obstacle_array3[i] = new Obstacle(game, float(i * 20) + CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 + 10, 20, 20);
		setObstacles(obstacle_array3[i]);

		obstacle_array4[i] = new Obstacle(game, float(i * 20) + CANVAS_WIDTH / 6, CANVAS_HEIGHT / 2 + 40, 20, 20);
		setObstacles(obstacle_array4[i]);
	}

	// Initialize ball
	ball->init();
}

LevelScreen::LevelScreen(const Game& mygame) : Screen(mygame)
{
	// Create players
	playerA = new Player(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 30, 50, 50, graphics::SCANCODE_A, graphics::SCANCODE_D);
	playerB = new Player(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - (CANVAS_HEIGHT - 30), 50, 50, graphics::SCANCODE_K, graphics::SCANCODE_L);

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