#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread> 

sf::TcpSocket socket;

void clientSideSocket() {
	
	char data[100];

	while (true) {
		printf("Digite algo: ");
		std::cin >> data;

		// TCP socket:
		if (socket.send(data, 100) != sf::Socket::Done)
		{
			printf("Erro on Sent\n");
			return;
		}
	}
	
}

int main(){

	sf::Time t1 = sf::seconds(1.f);
	sf::Socket::Status status = socket.connect("127.0.0.1", 53000, t1);
	if (status != sf::Socket::Done)
	{
		printf("Erro on Client\n");
	}

	clientSideSocket();

	return 0;
}
