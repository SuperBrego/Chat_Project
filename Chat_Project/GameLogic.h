#include <utility>
#include <string>

#include "Protocol.h"
#include "Character.h"

#pragma once

class GameLogic {

	int currentRound;

public:
	GameLogic() {
		currentRound = 0;
	}
	~GameLogic() {}

	void addClient(std::string login);

	void receiveMessage(std::string login, int action, int direction);

	int gameStepReady();

};
