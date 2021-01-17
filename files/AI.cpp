#include "AI.h"

void AI::update()
{
	if (ball->getPosY() < CANVAS_HEIGHT / 2) {
		float limit = ball->getSpeedX();
		if (limit < 0)limit *= -1;

		float ballPosx = ball->getPosX();
		float playerPosX = player->getPosX();

		if (ballPosx < playerPosX) {
			if (ballPosx > playerPosX - diff) {
				playerPosX -= limit;
				player->setPosX(playerPosX);
			}
			else {
				playerPosX -= diff;
				player->setPosX(playerPosX);
			}
		}
		else if (ballPosx > playerPosX) {
			if (ballPosx < playerPosX + diff) {
				playerPosX += limit;
				player->setPosX(playerPosX);
			}
			else {
				playerPosX += diff;
				player->setPosX(playerPosX);
			}
		}
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
