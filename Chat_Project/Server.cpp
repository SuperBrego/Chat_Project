#include "Server.h"

Server::Server() {
	connect();

}

int Server::run() {

	if (listener.accept(client) != sf::Socket::Done) {
		printf("Problema em conectar ao cliente.\n");
		return 0;
	}

	char data[100];
	std::size_t received;

	while (true) {


		// TCP socket:
		if (client.receive(data, 100, received) != sf::Socket::Done) {
			printf("Problema em conectar em receber os dados.\n");
			return 0;
		}
		printf("%s\n", data);
		printf("\n");
	}

	return 1;

}

void Server::connect() {	

	printf("= Iniciando conexao.\n");

	if (listener.listen(53000) != sf::Socket::Done) {
		printf("Problema em abrir socket.\n");
	}

	printf("= Listen de Porta Operante normalmente.\n");
	printf("== Aguardando Prompts.\n");

	std::thread waitingPrompts(&Server::run, this);
	//std::thread second(&Server::awaitConnection, this);

	waitingPrompts.join();
	
	//second.join();

}

