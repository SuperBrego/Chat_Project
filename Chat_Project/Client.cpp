#include "Client.h"

Client::Client() {

	if (!connect()) {
		printf("==== Houve um problema com a aplicacao. Por favor reinicie ==== ");
		exit(0);
	}

}

int Client::connect() {
	
	sf::Time t1 = sf::seconds(1.f);
	sf::Socket::Status status = socket.connect("192.168.0.5", 53000);
	if (status != sf::Socket::Done)
	{
		return 0;
	}

	return 1;
}

void Client::run() {


	char data[100];

	while (true) {
		printf("Digite algo: ");
		std::cin >> data;

		// TCP socket:
		if (socket.send(data, 100) != sf::Socket::Done) {
			printf("Erro on Sent.\n");
		}
	}

}