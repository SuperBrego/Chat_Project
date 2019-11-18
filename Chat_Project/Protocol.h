#include <stdio.h>
#include <iostream>
#include <string>

#include "Character.h"
#include "Message.h"

#pragma once

class Protocol {

	std::string clientName;
	Message message;
	Character playerData;

public:
	Protocol() {};
	~Protocol() {};

	void setClientName(std::string name);
	void setMessage(Message msg);
	void setPlayerCharacter(Character data);

	std::string getclientName();
	Message getMessage();
	Character getPlayerData();
	
	void toString();

};
