#include <iostream>
#include <thread>

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Protocol.h"

#pragma once

class Server {

	sf::TcpListener listener;
	sf::TcpSocket client;

	char data[100];
	std::size_t received;

	Protocol* currMessage;

public:
	Server();
	~Server() { }
	void connect();
	int run();
};