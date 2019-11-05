#include <iostream>

#include <SFML/Network.hpp>

#include "Protocol.h"

#pragma once

class Client {

	sf::TcpSocket socket;
	char* client_name;
	Protocol* message;

	void commandValidation();

public:
	Client();
	~Client() {}

	int connect();
	void run();
};
