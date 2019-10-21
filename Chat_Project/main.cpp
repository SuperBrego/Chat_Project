#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


void clientSideSocket() {
	sf::Time t1 = sf::seconds(1.f);
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.0.5", 53000, t1);
	if (status != sf::Socket::Done)
	{
		printf("Erro on Client\n");
		return;
	}
	
	char data[100] = "This is a test";

	// TCP socket:
	if (socket.send(data, 100) != sf::Socket::Done)
	{
		printf("Erro on Sent\n");
		return;
	}
}

int main(){

	//serverSideSocket();
	clientSideSocket();


	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
