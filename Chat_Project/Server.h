#include <iostream>
#include <thread>
#include <string>
#include <utility>      // std::pair, std::make_pair

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Protocol.h"
#include "GameLogic.h"
#include "Message.h"

#pragma once

class Server {

	// Create a socket to listen to new connections
	sf::TcpListener listener;
	// Create a list to store the future clients
	std::vector< std::pair<sf::TcpSocket*, std::string>> clients;
	// Create a selector
	sf::SocketSelector selector;
	// Recebe os dados vindo do cliente
	std::size_t received;

	GameLogic* gLogic;

public:
	Server();
	~Server() { }
	void run();
	void connectClient(sf::TcpSocket* client);	
	void treatMessage(Protocol* message);

	void replyClients();
	void replyClients(sf::TcpSocket* client);
};