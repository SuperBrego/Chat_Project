#include "Server.h"

Server::Server() {

	// Cria logica do jogo
	gLogic = new GameLogic();

	// Create a socket to listen to new connections
	listener.listen(52000);

	// Add the listener to the selector
	selector.add(listener);

	// Run Server
	run();

}

void Server::connectClient(sf::TcpSocket* client) {

	char login[100];

	// The client has sent some data, we can receive it
	if (client->receive(login, 100, received) == sf::Socket::Done) {
		
		std::string lg = login;
		// Send an answer
		std::string message = "Welcome, client " + lg;
		client->send(message.c_str(), message.size() + 1);

		// Add the new client to the clients list
		clients.push_back( std::make_pair(client, lg) );

		// Add the new client to the selector so that we will
		// be notified when he sends something
		selector.add(*client);
	}
	else delete client;
	
}

void Server::run() {

	bool running = true;

	// Endless loop that waits for new connections
	while (running) {

		// Make the selector wait for data on any socket
		if (selector.wait()) {

			// Test the listener
			if (selector.isReady(listener) && clients.size() < 2) {

				// The listener is ready: there is a pending connection
				sf::TcpSocket* client = new sf::TcpSocket;

				if (listener.accept(*client) == sf::Socket::Done) {

					connectClient(client);
				}
				else {
					// Error, we won't get a new connection, delete the socket
					delete client;
				}
			}
			else {
				// The listener socket is not ready, test all other sockets (the clients)
				for (std::vector< std::pair< sf::TcpSocket*, std::string>>::iterator it = clients.begin(); it != clients.end(); ++it) {

					sf::TcpSocket& client = *it->first;
					Protocol* item = new Protocol();

					if (selector.isReady(client)) {

						// The client has sent some data, we can receive it
						if (client.receive(item, sizeof(Protocol), received) == sf::Socket::Done) {
							treatMessage(item);

							if (gLogic->gameStepReady()) { 
								replyClients(); 
								gLogic->reset();
							}
						}
					}// Fim de Cliente pronto
				}// Fim de FOR de iterador
			}// Caso o Listener esteja ouvindo ainda e não fechou os clientes
		}// Seletor está esperando
	}

}

void Server::treatMessage(Protocol* proto) {

	Message msg = proto->getMessage();
	
	gLogic->receiveMessage(
		proto->getclientName(),
		msg.getMessageType(),
		msg.getTypeCommand()
	);
	
}

void Server::updateRenderPlayers(int currPlayers) {

	// Temos mais 
	if (currPlayers >= 2) {

		// The listener socket is not ready, test all other sockets (the clients)
		for (std::vector< std::pair< sf::TcpSocket*, std::string>>::iterator it = clients.begin(); it != clients.end(); ++it) {

			sf::TcpSocket* client = it->first;

			// Send an answer
			Protocol* retorno = new Protocol();

			Message msg;

			// 1- Render, 2- Status
			msg.setMessageType(1);

			// 1- No players, 2 - two players
			msg.setTypeCommand(2);

			retorno->setClientName("Server");
			retorno->setMessage(msg);

			client->send(retorno, sizeof(Protocol));
		}

	}


}

void Server::replyClients() {

	// The listener socket is not ready, test all other sockets (the clients)
	for (std::vector< std::pair< sf::TcpSocket*, std::string>>::iterator it = clients.begin(); it != clients.end(); ++it) {

		sf::TcpSocket* client = it->first;
		int healthPoints = gLogic->getPlayerHP( it->second );
		
		// Send an answer
		Protocol* retorno = new Protocol();
		
		Message msg;
		// 1- Render, 2- Status
		msg.setMessageType(2);
		msg.setTypeCommand(0);
		retorno->setClientName("Server");
		retorno->setMessage(msg);

		// Updated Health Points
		Character charact;
		charact.setHealthPoints(healthPoints);
		retorno->setPlayerCharacter(charact);

		client->send(retorno, sizeof(Protocol));
	}

	printf("\n=== Mensagens Enviadas === \n");

}

void Server::replyClients(sf::TcpSocket* client) {
	
	// Send an answer
	Protocol* retorno = new Protocol();
	Message msg;
	// 1- Render, 2- Status
	msg.setMessageType(2);
	msg.setTypeCommand(0);
	Character charact;
	//msg.setServerReply("Recebi sua mensagem.");
	retorno->setClientName("Server");
	retorno->setMessage(msg);
	retorno->setPlayerCharacter(charact);

	client->send(retorno, sizeof(Protocol));

}