#include <iostream>
#include <string>
#include <thread>

#include <SFML/Network.hpp>

#include "Protocol.h"
#include "Render.h"

#pragma once

class Client {

	sf::TcpSocket socket;
	std::string client_name;
	Protocol* message;
	Render* render;
	
	int currentHealth;
	int direction;
	int state;

	bool readySent;
	bool endgame;

	void commandValidation();

public:
	Client();
	~Client() {}

	int connect();
	void startRender();
	void run();
	void extractReply(Protocol* reply);
	

	void setHealthPoints(int hp) { currentHealth = hp; }
	int getHealthPoints() { return currentHealth; }
};