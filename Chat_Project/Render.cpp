#include "Render.h"

void introText() {

	printf("============ Inicializando Sistema ============");
	printf("Digite a funcao desta aplicacao:\n- 1: Cliente\n- 2: Servidor");

}

void Render::createWindow() {
	window->create(sf::VideoMode(1200, 600), "MBA - Battle Your Friends");
	
	// change the position of the window (relatively to the desktop)
	window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 4, sf::VideoMode::getDesktopMode().height / 4));

}


void Render::startApplication() {
	window = new sf::RenderWindow();

	createWindow();

}

void Render::awaitScreen() {

	background = sf::RectangleShape(sf::Vector2f(1200.f, 400.f));
	background.setOrigin(sf::Vector2f(0.0f, -100.0f));

	sf::Texture texture;
	if (!texture.loadFromFile("../Resources/arena_background.png")) { }
	background.setTexture(&texture);

	printf("Largura: %d\nAltura: %d\n",texture.getSize().x, texture.getSize().y);

	// run the program as long as the window is open
	while (window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window->close();
		}

		// clear the window with black color
		window->clear(sf::Color::Black);

		// draw everything here...
		window->draw(background);
		

		// end the current frame
		window->display();
	}

}