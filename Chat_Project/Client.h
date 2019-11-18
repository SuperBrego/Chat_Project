#include <iostream>
#include <string>

#include <SFML/Network.hpp>

#include "Protocol.h"

#pragma once

class Client {

	sf::TcpSocket socket;
	std::string client_name;
	Protocol* message;
	Character playerData;

	void commandValidation();

public:
	Client();
	~Client() {}

	int connect();
	void run();
	void extractReply(Protocol* reply);
};
