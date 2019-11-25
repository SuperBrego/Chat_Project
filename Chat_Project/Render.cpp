#include "Render.h"

/* Inicia a janela principal, sprite de jogadores, background, corações, itens e textos.
*/
void Render::startApplication() {

	endgame = 0;

	window = new sf::RenderWindow();

	createWindow();
	settingUpPlayers();
	settingUpBg();
	settingUpHearts();
	settingUpItens();
	settingUpText();


}

/* Cria a Render Window e posiciona ela no centro da tela do Desktop. */
void Render::createWindow() {
	window->create(sf::VideoMode(1200, 600), "MBA - Battle Your Friends");

	// change the position of the window (relatively to the desktop)
	window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 4, sf::VideoMode::getDesktopMode().height / 4));

}

/* Cria a imagem de background no fundo da aplicação. */
void Render::settingUpBg() {

	background = new sf::RectangleShape();
	background->setSize(sf::Vector2f(1200.f, 400.f));
	background->setOrigin(sf::Vector2f(0.0f, -100.0f));

	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile("../Resources/arena_background.png")) {
		printf("Nao conseguiu carregar textura.");
	}
	background->setTexture(texture);
}

/* Cria e posiciona os sprites dos jogadores. */
void Render::settingUpPlayers() {

	// 1/4 screen
	int x1 = (window->getSize().x / 4) * -1;
	int y = (window->getSize().y / 4) * -2 - 90;

	// Blue Mage
	character1 = sf::RectangleShape(sf::Vector2f(60, 60));
	character1.setOrigin(sf::Vector2f(x1, y));

	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile("../Resources/characters/blue_mage_idle.png")) {
		printf("Problema em carregar textura do Player 1. Conferir caminho.\n");
	}
	character1.setTexture(texture);

	// 3/4 screen
	int x2 = (window->getSize().x / 4) * -3;
	// Red Mage
	character2 = sf::RectangleShape(sf::Vector2f(60, 60));
	character2.setOrigin(sf::Vector2f(x2, y));

	texture = new sf::Texture();
	if (!texture->loadFromFile("../Resources/characters/red_mage_idle.png")) {
		printf("Problema em carregar textura do Player 2. Conferir caminho.\n.");
	}
	character2.setTexture(texture);

}

void Render::settingUpItens() {

	sword = new sf::Texture();
	if (!sword->loadFromFile("../Resources/Itens/Sword.png")) {
		printf("Problema em carregar textura do item ESPADA. Conferir caminho.\n");
	}

	shield = new sf::Texture();
	if (!shield->loadFromFile("../Resources/Itens/Shield.png")) {
		printf("Problema em carregar textura do item ESCUDO. Conferir caminho.\n");
	}

	dodge = new sf::Texture();
	if (!dodge->loadFromFile("../Resources/Itens/Dodge.png")) {
		printf("Problema em carregar textura do item ESQUIVA. Conferir caminho.\n");
	}

	/* Iremos desenhar os icones em um contorno de semi-círculo */
	float radius = 70;
	float twoPI = 2 * 3.14;

	// Semi-circule positions - x e y do jogador menos um pouco.
	int y = character1.getOrigin().y + 60;
	int x = character1.getOrigin().x + 30;

	sf::RectangleShape* itemPlaceHolder;

	for (float i = 0.0; i <= twoPI / 2; i += 1) {

		itemPlaceHolder = new sf::RectangleShape();

		itemPlaceHolder->setOrigin((sin(i) * radius) + x, (cos(i) * radius) + y);

		itemPlaceHolder->setSize(sf::Vector2f(30, 30));

		itemPlaceHolder->setTexture(sword);

		itens.push_back(itemPlaceHolder);
	}

	// Selection circle
	selection = new sf::CircleShape();
	selection->setRadius(20);
	selection->setFillColor(sf::Color::Yellow);
	selection->setOrigin(
		itens.at(direction)->getOrigin().x + 10, 
		itens.at(direction)->getOrigin().y + 20
	);

}

void Render::settingUpHearts() {

	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile("../Resources/heart.png")) {
		printf("Nao foi possivel carregar textura HEART. Conferir caminho.\n");
	}

	// Player Origin
	int x = character1.getOrigin().x + 50;
	int y = window->getView().getViewport().height - 550;

	sf::RectangleShape* heart;
	for (int i = 0; i < 5; i++) {
		heart = new sf::RectangleShape();
		heart->setSize(sf::Vector2f(30, 30));
		heart->setOrigin(sf::Vector2f(x - (i * 35), y));
		heart->setTexture(texture);
		hearts.push_back(heart);
	}

	// Enemy hearts
	x = character2.getOrigin().x + 50;
	y = window->getView().getViewport().height - 550;

	for (int i = 0; i < 5; i++) {
		heart = new sf::RectangleShape();
		heart->setSize(sf::Vector2f(30, 30));
		heart->setOrigin(sf::Vector2f(x + (i * 35), y));
		heart->setTexture(texture);
		enemyHearts.push_back(heart);
	}

}

void Render::settingUpText() {

	_8bitFont = new sf::Font();
	if (!_8bitFont->loadFromFile("../Resources/fonts/8bit16.ttf")) {
		printf("Erro em carregar Fonte.\n");
	}

	// Set Spacebar
	spaceBar = new sf::RectangleShape();
	spaceBar->setSize(sf::Vector2f(150, 75));
	spaceBar->setOrigin(sf::Vector2f(-(background->getSize().x / 2) + 50, -500));

	sf::Texture* txt = new sf::Texture();
	if (!txt->loadFromFile("../Resources/icons/spacebar.png")) {
		printf("Nao consiguiu carregar Spacebar");
	}
	spaceBar->setTexture(txt);

	// Adding Txt
	spaceBarTxt = new sf::Text();
	spaceBarTxt->setFont(*_8bitFont);
	spaceBarTxt->setOrigin(spaceBar->getOrigin().x - 25, spaceBar->getOrigin().y - 10);
	spaceBarTxt->setString("ATAQUE");
	spaceBarTxt->setFillColor(sf::Color::Red);
	spaceBarTxt->setCharacterSize(20); // in pixels, not points!

	// Waiting Text
	waitingTxt = new sf::Text();
	waitingTxt->setFont(*_8bitFont);
	waitingTxt->setOrigin(-100, -300);
	waitingTxt->setString("AGUARDANDO RESPOSTA");
	waitingTxt->setFillColor(sf::Color::Red);
	waitingTxt->setCharacterSize(60); // in pixels, not points!
}

void Render::Update() {

	selection->setOrigin(itens.at(direction)->getOrigin());

	for (int i = 0; i < itens.size(); i++) {

		if (state == 0) {
			itens.at(i)->setTexture(sword, true);
			spaceBarTxt->setString("ATAQUE");
		}
		else if (state == 1) {
			itens.at(i)->setTexture(shield, true);
			spaceBarTxt->setString("DEFESA");
		}
		else {
			itens.at(i)->setTexture(dodge, true);
			spaceBarTxt->setString("ESQUIVA\n(50%)");
		}
	}
}

void Render::drawGame() {

	// Desenha Fundo
	window->draw(*background);

	// Desenha personagens
	window->draw(character1);

	//if (renderPlayer2) {
	window->draw(character2);

	// Desenha os corações.
	for (int i = 0; i < enemyCurrHearts; i++) {
		window->draw(*enemyHearts.at(i));
	}

	//}
	
	// Desenha os corações.
	for (int i = 0; i < currentHearts; i++) {
		window->draw(*hearts.at(i));
	}
	
	// Desenha Círculo de selecionar opção e opções.
	window->draw(*selection);
	for (int i = 0; i < itens.size(); i++) {
		window->draw(*itens.at(i));
	}

	// Desenha barra de espaço e texto exibindo estado atual.
	window->draw(*spaceBar);
	window->draw(*spaceBarTxt);

	if (waitingResponse) {

		if (endgame == 2) {

			if (currentHearts > 0) {
				waitingTxt->setString("YOU WIN");
				sf::Texture* txt = new sf::Texture();
				txt->loadFromFile("../Resources/characters/red_mage_dead.png");
				character2.setTexture(txt);
			}
			else {
				waitingTxt->setString("YOU LOSE");
				sf::Texture* txt = new sf::Texture();
				txt->loadFromFile("../Resources/characters/blue_mage_dead.png");
				character1.setTexture(txt);
			}
		}
		else if (endgame == 1) {
			waitingTxt->setString("YOU ALL LOSE");
			sf::Texture* txt = new sf::Texture();
			txt->loadFromFile("../Resources/characters/red_mage_dead.png");
			character2.setTexture(txt);
			txt = new sf::Texture();
			txt->loadFromFile("../Resources/characters/blue_mage_dead.png");
			character1.setTexture(txt);
		}
		
		window->draw(*waitingTxt);

	}

}