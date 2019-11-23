#include "GameLogic.h"

void GameLogic::receiveMessage(std::string login, int action, int direction) {

	PlayerAction* pp = new PlayerAction();
	pp->login = login;
	pp->action = action;
	pp->direction = direction;
	pp->currentHealthPoints = 0;
	playerMessages.push_back(pp);

	if (playerMessages.size() >= 2) {
		gameStep();
	}

}

void GameLogic::reset() {

	playerMessages.clear();
	readyStep = 0;

}

void GameLogic::gameStep() {

	srand(NULL);

	PlayerAction* player1 = playerMessages.at(0);
	PlayerAction* player2 = playerMessages.at(1);

	if (player1->action == 1) {

		if (player2->action == 3) {
			if ((rand() % 100) > 50 ) {
				player2->currentHealthPoints = -1;
			}
		}
		else if (player2->action == 2) {
			if (player1->direction == player2->direction) player2->currentHealthPoints = 1;
			else player2->currentHealthPoints = -1;
		}
		else if(player2->action == 1){
			player1->currentHealthPoints = -1;
			player2->currentHealthPoints = -1;
		}
	}
	else if (player1->action == 2) {
		if (player2->action == 1 && player1->direction == player2->direction) player1->currentHealthPoints = 1;
		else player1->currentHealthPoints = -1;
	}
	else if (player2->action == 1 && player1->action == 3) {
		if ((rand() % 100) > 50) {
			player1->currentHealthPoints = -1;
		}
	}

	readyStep = 1;
}