#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>

#pragma once

class Server {

	sf::TcpListener listener;
	sf::TcpSocket clients;
	char data[100];
	std::size_t received;

public:
	Server();
	~Server() { }
	void connect();
	//int awaitConnection(int currClient);
	int awaitConnection();

	void run();
};