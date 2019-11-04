#include "Server.h"

Server::Server() {
	
	connect();
	
}



int Server::awaitConnection() {

	if (listener.accept(clients) != sf::Socket::Done)
	{
		printf("Problema em receber.\n");
		return 0;
	}

	return 1;

}

void Server::connect() {	

	int num = 1;
	sf::Thread thread(&Server::awaitConnection);
	//sf::Thread second_Client(&awaitConnection);

	//first_Client.launch();

	printf("DEBUG: Sucesso no Listen.\n");

}

void Server::run() {
	while (true) {
		if (clients.receive(data, 100, received) != sf::Socket::Done)
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