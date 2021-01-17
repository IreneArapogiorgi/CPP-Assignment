#include "levelscreen.h"

void LevelScreen::createBall()
{
	int random_variable = rand() % 2;

	if (random_variable == 1)
	{
		ball = new Ball(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 30, 20, 20);
		ball->setKeys(playerA_keyL, playerA_keyR);
		playerTurn = 1;
	}
	else {
		ball = new Ball(game, CANVAS_WIDTH / 2, 30, 20, 20);
		ball->setKeys(playerB_keyL, playerB_keyR);
		playerTurn = 2;
	}
}

void LevelScreen::createPlayers()
{
	playerA = new Player(game, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 10, 100, 20, playerA_keyL, playerA_keyR, 6 - level);
	playerB = new Player(game, CANVAS_WIDTH / 2, 10, 100, 20, playerB_keyL, playerB_keyR, 6 - level);

	players[0] = playerA;
	players[1] = playerB;
}

void LevelScreen::createObstacles()
{
	int space = 0;
	bool t = false;
	if (level == 1) t = true;

	for (int i = 0; i < OBSTACLE_ROWS; i++) {
		obstacles[i] = new Obstacle * [OBSTACLES_PER_ROW * level];
		for (int j = 0; j < (OBSTACLES_PER_ROW * level); j++) {
			if (!t && j > (OBSTACLES_PER_ROW * level) / 2 - 1) {
				space = 80;
				t = true;
			}
			obstacles[i][j] = new Obstacle(game, float(j * 120 / level) + st[i + (level - 1) * 4][0] * LEVELSCREEN_WIDTH + space, st[i + (level - 1) * 4][1] * LEVELSCREEN_HEIGHT, 30, 20, level);
			obstacles[i][j]->init();
		}
		if (level != 1) t = false;
		space = 0;
	}
}

void LevelScreen::update()
{
	// Proceed to menu screen if Q is pressed
	if (getKeyState(SCANCODE_Q))
	{
		status = STATUS_ESCAPE;
	}

	if (ball && ball->respawn()) {
		if (playerA) playerA->update();
		if (playerB) {
			if (AIflag) {
				ai->update();
			}
			else {
				playerB->update();
			}
		}

		ball->update();

		// Check collision between ball and obstacles
		for (int i = 0; i < OBSTACLE_ROWS; i++) {
			int index = ball->checkCollision(reinterpret_cast<GameObject**>(obstacles[i]), OBSTACLES_PER_ROW * level);

			if (index != -1)
			{
				// Play collision sound
				string sound = string(ASSET_PATH) + "collision_sound.wav";
				playSound(sound, 0.2f);

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

		if (!AIflag) {
			ball->start();
		}
		else {
			if (playerTurn == 2) {
				ai->update();
			}
			else if (playerTurn == 1) {
				ball->start();
			}
		}
	}

	// Update each player's life
	int bounds = ball->outOfbounds();

	if (bounds == 1)
	{
		if (playerB && playerB->getLife() > 0)
		{
			playerTurn = 2;
			playerB->reduceLife();
			ball->setPosX(CANVAS_WIDTH / 2);
			ball->setPosY(30);
			ball->setKeys(playerB_keyL, playerB_keyR);
		}
	}

	if (bounds == 2)
	{
		if (playerA && playerA->getLife() > 0)
		{
			playerTurn = 1;
			playerA->reduceLife();
			ball->setPosX(CANVAS_WIDTH / 2);
			ball->setPosY(CANVAS_HEIGHT - 30);
			ball->setKeys(playerA_keyL, playerA_keyR);
		}
	}

	// End game if each of the players loses
	if (playerA && playerB)
	{
		if (playerA->getLife() == 0) {
			winner = '1';
			status = STATUS_END;
		}
		else if (playerB->getLife() == 0) {
			winner = '2';
			status = STATUS_END;
		}
	}
}

void LevelScreen::draw()
{
	// Draw background
	br.texture = string(ASSET_PATH) + "levelscreen.png";
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.45f;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	// Draw players
	if (playerA && playerB)
	{
		playerA->draw();
		setOrientation(180);
		playerB->draw();
		resetPose();
	}

	// Display UI info
	if (playerA && playerB)
	{
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		br.fill_opacity = 1.0f;
		setFont(string(ASSET_PATH) + "info_font.ttf");

		char info[9];
		sprintf_s(info, "Life: %d", playerA->getLife());
		drawText(INFOTEXT_POSX, INFOTEXT_POSY, INFOTEXT_SIZE, info, br);

		sprintf_s(info, "Life: %d", playerB->getLife());
		drawText(INFOTEXT_POSX, CANVAS_HEIGHT - INFOTEXT_POSY, INFOTEXT_SIZE, info, br);
	}

	// Draw ball
	if (ball)
	{
		ball->draw();
	}

	// Draw obstacles
	if (obstacles) {
		for (int i = 0; i < OBSTACLE_ROWS; i++) {
			for (int j = 0; j < OBSTACLES_PER_ROW * level; j++) {
				if (obstacles[i][j] && obstacles[i][j]->isAlive()) {
					obstacles[i][j]->draw();
				}
			}
		}
	}
}

void LevelScreen::init()
{
	// Create game objects
	createPlayers();
	createBall();
	createObstacles();

	// Set speed difficulty
	if (diff == 1) ball->setSpeed(2.3f);

	// Play against computer, if chosen by the user
	if (AIflag)
	{
		ai = new AI(game, playerB, ball);

		// Set AI difficulty
		if (diff == 1) ai->setDiff(diff);
	}
}

LevelScreen::LevelScreen(const Game& mygame) : Screen(mygame)
{
	self = STATUS_LEVEL;
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
		for (int j = 0; j < OBSTACLES_PER_ROW * level; j++) {
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

	// Delete AI
	if (ai)
	{
		delete ai;
	}
}