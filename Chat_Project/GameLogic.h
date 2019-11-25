#include <utility>
#include <string>
#include <vector>
#include <time>

#include "Protocol.h"
#include "Character.h"

#pragma once

struct PlayerAction {
	std::string login;
	int action, direction;
	int currentHealthPoints;
};

class GameLogic {

	std::vector<PlayerAction*> playerMessages;
	int readyStep;



public:
	GameLogic() {
		readyStep = 0;
	}
	~GameLogic() {}

	void receiveMessage(std::string login, int action, int direction, int healthPoints);

	void reset();
	void gameStep();

	int gameStepReady() { return readyStep; }
	int getPlayerHP(std::string playerName);

};
