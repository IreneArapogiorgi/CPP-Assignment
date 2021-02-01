#include "AI.h"

void AI::update()
{
	// If ball is found half the canvas up, close to AI-player
	if (ball->getPosY() < CANVAS_HEIGHT / 2) {
		// Set limit to AI movement
		float limit = ball->getSpeedX();
		if (limit < 0)limit *= -1;

		float ballPosX = ball->getPosX();
		float playerPosX = player->getPosX();

		// If ball is found to the left regarding AI's position
		if (ballPosX < playerPosX) {
			// Move AI-player based on distance from ball on axis x
			if (ballPosX > playerPosX - diff) {
				playerPosX -= limit;
				player->setPosX(playerPosX);
			}
			else {
				playerPosX -= diff;
				player->setPosX(playerPosX);
			}
		}
		// If ball is found to the right regarding AI's position
		else if (ballPosX > playerPosX) {
			// Move AI-player based on distance from ball on axis x
			if (ballPosX < playerPosX + diff) {
				playerPosX += limit;
				player->setPosX(playerPosX);
			}
			else {
				playerPosX += diff;
				player->setPosX(playerPosX);
			}
		}

		// Keep player within canvas borders
		if (playerPosX - player->getWidth() / 2 < 0) { player->setPosX(player->getWidth() / 2); }
		if (playerPosX + player->getWidth() / 2 > CANVAS_WIDTH) { player->setPosX(CANVAS_WIDTH - player->getWidth() / 2); }
	}

	// Wait before playing
	float temp = getGlobalTime();

	if (!ball->respawn()) {
		if (temp > timer && flag) {
			timer = temp;
			flag = false;
		}

		if (timer + 1000.0 < temp) {
			flag = true;
			ball->startBall();
		}
		player->startingPos();
	}
}

void AI::setDiff(unsigned int diff)
{
	// Increase difficulty if chosen on menu
	if (diff == 1)
	{
		this->diff = 6;
	}
}

AI::AI(const Game& mygame, Player* player, Ball* ball) : game(mygame), player(player), ball(ball)
{
}

AI::~AI()
{
}
