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
		std::string message = "Bem vindo, cliente " + lg;
		client->send(message.c_str(), message.size() + 1);

		// Adiciona o novo cliente para lista de clientes.
		clients.push_back( std::make_pair(client, lg) );

		// Adiciona cleinte ao seletor para ser notificado quando ele enviar algo.
		selector.add(*client);

		if (clients.size() > 1) {
			updateRenderPlayers();
		}


	}
	else delete client;
	
}

void Server::run() {

	running = true;

	// Loop infinito que aguarda novas conexões.
	while (running) {

		// Faz o seletor aguardar por qualquer pacote no socket.
		if (selector.wait()) {

			// Testa o Listener para receber novas conexões enquanto estiver pronto 
			// Ou ainda não tem dois clientes.
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

				// Se não estiver pronto, ou tiver os clientes, testa os outros sockets (os clientes).
				for (std::vector< std::pair< sf::TcpSocket*, std::string>>::iterator it = clients.begin(); it != clients.end(); ++it) {

					sf::TcpSocket& client = *it->first;
					Protocol* item = new Protocol();

					if (selector.isReady(client)) {

						// O cliente tem algum pacote a enviar, podemos receber
						if (client.receive(item, sizeof(Protocol), received) == sf::Socket::Done) {
							treatMessage(item);

							if (gLogic->gameStepReady()) { 
								replyClients(); 
								gLogic->reset();
							}
							// updateRenderPlayers(clients.size());
						}
					}// Fim de Cliente pronto
				}// Fim de FOR de iterador
			}// Caso o Listener esteja ouvindo ainda e não fechou os clientes
		}// Seletor está esperando
	}

	listener.close();

}

// Trata mensagem do jogo.
void Server::treatMessage(Protocol* proto) {

	Message msg = proto->getMessage();
	
	gLogic->receiveMessage(
		proto->getclientName(),
		msg.getMessageType(),
		msg.getTypeCommand(),
		proto->getHealthPoints()
	);
	
	if (proto->getHealthPoints() < 1) {
		numDeath++;
		callEndgame();
	}

}

void Server::updateRenderPlayers() {

	// The listener socket is not ready, test all other sockets (the clients)
	for (std::vector< std::pair< sf::TcpSocket*, std::string>>::iterator it = clients.begin(); it != clients.end(); ++it) {

		sf::TcpSocket* client = it->first;

		// Send an answer
		Protocol* retorno = new Protocol();
		Message msg;

		// 1- Render, 2- Status
		msg.setMessageType(1);

		// 1- 1 Player, 2 - two players, 3 - enemy player healthpoints
		msg.setTypeCommand(2);

		retorno->setClientName("Server");
		retorno->setMessage(msg);

		client->send(retorno, sizeof(Protocol));
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
		// 1- Render, 2- Status, 3- Endgame
		msg.setMessageType(2);
		msg.setTypeCommand(0);
		retorno->setClientName("Server");
		retorno->setMessage(msg);

		// Updated Health Points
		retorno->setHealthPoints(healthPoints);

		client->send(retorno, sizeof(Protocol));
	}

	printf("\n=== Mensagens Enviadas === \n");

}

/* A partir dessa função, irá avisar aos jogadores para terminar o jogo. 
** Cada um vai acabar seu jogo. Se tiver energia, vai considerar ganho. 
** Servidor ainda mandará mensagem através do tipo de comando para informar se tiver empate.
*/
void Server::callEndgame() {
	
	running = false;

	// The listener socket is not ready, test all other sockets (the clients)
	for (std::vector< std::pair< sf::TcpSocket*, std::string>>::iterator it = clients.begin(); it != clients.end(); ++it) {

		sf::TcpSocket* client = it->first;

		// Send an answer
		Protocol* retorno = new Protocol();

		Message msg;
		// 1- Render, 2- Status, 3- Endgame
		msg.setMessageType(3);
		
		// 0- Sem empate, 1 Empate
		if(numDeath > 1) msg.setTypeCommand(1);
		else msg.setTypeCommand(0);

		retorno->setClientName("Server");
		retorno->setMessage(msg);

		client->send(retorno, sizeof(Protocol));
	}

}