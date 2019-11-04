#include <SFML/Network.hpp>
#include <iostream>

#pragma once

class Client {

	sf::TcpSocket socket;

public:
	Client();
	~Client() {}

	int connect();
	void run();
};
