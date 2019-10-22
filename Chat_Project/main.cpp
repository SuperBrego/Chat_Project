#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

void clientSide() {

	sf::Time tc1 = sf::seconds(5.f);
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.0.5", 53000, tc1);
	if (status != sf::Socket::Done) 
	{
		printf("Erro com Connect.\n");
	}

	char data[100] = "This is a test";

	// TCP socket:
	if (socket.send(data, 100) != sf::Socket::Done)
	{
		printf("Error on sending data");
	}
	
}



int main(){

	sf::RenderWindow window(sf::VideoMode(800, 400), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	clientSide();

	while (window.isOpen()) {
		sf::Event event;
		
		while ( window.pollEvent(event) ) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();

		printf("Waiting input: \n");
	}

	return 0;
}
