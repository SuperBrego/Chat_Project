#include <string>
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>

#pragma once

class Render {
	sf::RenderWindow* window;

	int currentHearts;
	// 0 - Attack, 1 - Defend, 3 - Dodge
	int state;
	// 0 cima,  1 esquerda, 2 direita, 3 baixo
	int direction;
	// Esperando sv.
	bool waitingResponse;
	int endgame;

	// Render Second player
	bool renderPlayer2;
	int enemyCurrHearts;

	// Shapes
	sf::RectangleShape* background;
	sf::RectangleShape* spaceBar;
	sf::RectangleShape character1, character2;

	std::vector<sf::RectangleShape*> itens;
	std::vector<sf::RectangleShape*> hearts;
	std::vector<sf::RectangleShape*> enemyHearts;

	sf::Text* spaceBarTxt;
	sf::Text* playerName;

	sf::Texture* shield;
	sf::Texture* sword;
	sf::Texture* dodge;

	sf::CircleShape* selection;

	sf::Text* waitingTxt;
	sf::Font* _8bitFont;

	void createWindow();

public:
	Render() {}

	void startApplication();
	void settingUpBg();
	void settingUpPlayers();
	void settingUpItens();
	void settingUpHearts();
	void settingUpText();

	void drawGame();
	void Update();

	//Setters
	void setCurrentHearts(int hearts) { currentHearts = hearts; }
	void setCurrentState(int st) { state = st; }
	void setCurrentDirection(int dir) { direction = dir; }
	void setRenderSecondPlayer(bool rend) { renderPlayer2 = rend; }
	void setWaitingServer(bool isWaiting) { waitingResponse = isWaiting; }
	void setEndgame(int end) { endgame = end; }

	// Getters
	sf::RenderWindow* getWindow() { return window; }
};