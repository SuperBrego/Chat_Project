#include "Client.h"

Client::Client() {

	
	char exit_prompt;
	if (!connect()) {
		printf("==== Houve um problema com a aplicacao. Por favor reinicie. ====\n");
		std::cin >> exit_prompt;
		std::cin.ignore();
	}
	else {

		printf("==== Digite seu login: ====\n");
		std::cin >> client_name;
		
		message = new Protocol();
		message->setClientName(client_name);

		run();
	}

}

int Client::connect() {
	
	sf::Time t1 = sf::seconds(1.f);
	sf::Socket::Status status = socket.connect("191.4.195.245", 53000);
	
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
		while (dir) {
			while (dir > 3 || dir < 0) {
				printf("Comando Invalido.\n");
				printf("=== Qual o tipo de acao: ===\n");
				printf("- 1: Ataque\n");
				printf("- 2: Bloquear\n");
				printf("- 3: Esquivar\n");
				printf("==================\n");
				std::cin >> dir;
			}
		}
	}
	//Esquiva
	else {
		dir = 0;
	}
	printf("\n");

	message->setMessageType(type);
	message->setDirection(dir);
}