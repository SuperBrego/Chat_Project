#include <iostream>
#include <string>

#include <SFML/Network.hpp>

#include "Protocol.h"
#include "Render.h"

#pragma once

class Client {

	sf::TcpSocket socket;
	std::string client_name;
	Protocol* message;
	Character playerData;
	Render* render;

	int numPlayers;

	void commandValidation();

public:
	Client();
	~Client() {}

	int connect();
	void run();
	void extractReply(Protocol* reply);
	void ClientRender();
};
