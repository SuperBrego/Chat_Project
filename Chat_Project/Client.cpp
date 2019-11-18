#include "Client.h"

Client::Client() {

	client_name = "";

	char exit_prompt;
	if (!connect()) {
		printf("==== Nao ha nenhum servidor rodando. Por favor entre em contato com o servidor e tente novamente. ====\n");
		std::cin >> exit_prompt;
		std::cin.ignore();

	}
	else {

		char login[100];

		printf("==== Digite seu login: ====\n");
		std::cin >> login;
		
		// Nome do cliente para o Protocolo
		client_name = login;

		// Envia Login
		if (socket.send(login, 100) == sf::Socket::Done) {
		
			// Receive an answer from the server
			char buffer[1024];
			std::size_t received = 0;
			socket.receive(buffer, sizeof(buffer), received);
			std::cout << buffer << std::endl;

			message = new Protocol();
			message->setClientName(client_name);
			message->setPlayerCharacter(playerData);

			run();
		}
	}

}

int Client::connect() {
	
	std::string ip;
	std::cout << "Digite o IP destino: \n";
	std::cin >> ip;

	sf::Time t1 = sf::seconds(1.f);
	sf::Socket::Status status = socket.connect(ip, 52000);
	
	if (status != sf::Socket::Done) {
		return 0;
	}

	return 1;
}

void Client::run() {

	while (true) {
		
		commandValidation();

		printf("=== Enviando Mensagem ===\n");
		// TCP socket:
		if (socket.send(message, sizeof(Protocol)) != sf::Socket::Done) {
			printf("Erro on Sent.\n");
		}

		// Receive an answer from the server
		Protocol* serverReply = new Protocol();
		std::size_t received = 0;
		sf::Socket::Status status = socket.receive(serverReply, sizeof(Protocol), received);

		printf("== Aguardando resposta do servidor ==\n");
		while (status != sf::Socket::Done) { }
		printf("== Retorno ==\n");
		serverReply->toString();
		printf("== ------------------------------ ==\n");
		extractReply(serverReply);
	}

}

void Client::commandValidation() {

	int type;
	int dir;

	printf("=== Qual o tipo de acao: ===\n");
	printf("- 1: Ataque\n");
	printf("- 2: Bloquear\n");
	printf("- 3: Esquivar\n");
	printf("==================\n");
	std::cin >> type;
	while (type > 3 || type < 1) {
		printf("Comando Invalido.\n");
		printf("=== Qual o tipo de acao: ===\n");
		printf("- 1: Ataque\n");
		printf("- 2: Bloquear\n");
		printf("- 3: Esquivar\n");
		printf("==================\n");
		std::cin >> type;
	}
	printf("\n");
	
	if (type < 3) {
		printf("=== Qual direcao? ===\n");
		printf("- 0: Cima\n");
		printf("- 1: Baixo\n");
		printf("- 2: Esquerda\n");
		printf("- 3: Direita\n");
		printf("==================\n");
		std::cin >> dir;
		while (dir > 3 || dir < 0) {
			printf("Comando Invalido.\n");
			printf("=== Qual o tipo de acao: ===\n");
			printf("- 0: Cima\n");
			printf("- 1: Baixo\n");
			printf("- 2: Esquerda\n");
			printf("- 3: Direita\n");
			printf("==================\n");
			std::cin >> dir;
		}
		
	}
	//Esquiva
	else {
		dir = 0;
	}
	printf("\n");

	Message msg;

	msg.setMessageType(type);
	msg.setDirection(dir);
	message->setMessage(msg);
}

void Client::extractReply(Protocol* reply) {

}