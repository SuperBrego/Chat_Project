#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>

#pragma once

class Server {

	sf::TcpListener listener;
	sf::TcpSocket client;
	char data[100];
	std::size_t received;

	void connect() {
		// bind the listener to a port
		if (listener.listen(53000) != sf::Socket::Done)
		{
			printf("Problema na conexao.\n");
		}

		printf("Sucesso no listen.\n");

		if (listener.accept(client) != sf::Socket::Done)
		{
			printf("Problema em receber.\n");
		}
	}

	void run() {
		while (true) {
			if (client.receive(data, 100, received) != sf::Socket::Done)
			{
				//printf("Problema na transferencia.\n");
				std::cout << "Received " << received << " bytes" << std::endl;
			}
			else {
				std::cout << "Data " << data << std::endl;
				std::cout << "Received " << received << " bytes" << std::endl;
			}
		}
	}
};