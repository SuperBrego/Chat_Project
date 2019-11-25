#include <stdio.h>
#include <iostream>
#include <string>

#include "Character.h"
#include "Message.h"

#pragma once

class Protocol {

	std::string clientName;
	Message message;
	int currentHealth;

public:
	Protocol() {
		message.setServerReply("");
	};
	~Protocol() {};

	void Protocol::setClientName(std::string name) { clientName = name; }
	void Protocol::setMessage(Message msg) { message = msg; }
	void Protocol::setHealthPoints(int hp) { currentHealth = hp; }

	std::string Protocol::getclientName() { return clientName; }
	Message Protocol::getMessage() { return message; }
	int Protocol::getHealthPoints() { return currentHealth; }
	
	void toString();

};
