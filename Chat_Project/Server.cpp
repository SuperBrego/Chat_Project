#include "Server.h"

Server::Server() {
	connect();
}

int Server::run() {

	sf::TcpSocket client;

	if (listener.accept(client) != sf::Socket::Done) {
		printf("Problema em conectar ao cliente.\n");
		return 0;
	}
	//https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1SocketSelector.php
	Protocol* item = new Protocol();
	std::size_t received;

	while (true) {

		// TCP socket:
		if (client.receive(item, 100, received) != sf::Socket::Done) {
			printf("Problema em conectar em receber os dados.\n");
			return 0;
		}

		item->toString();
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
	printf("== Aguardando Prompts ==\n");

	std::thread first_client(&Server::run, this);
	std::thread second_client(&Server::run, this);

	first_client.join();
	//second_client.join();

}

