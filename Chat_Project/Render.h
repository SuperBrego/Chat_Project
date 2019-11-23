#include <string>

#include <SFML/Graphics.hpp>

#pragma once

class Render {
	sf::RenderWindow* window;

	// Shapes
	sf::RectangleShape background;
	sf::RectangleShape character1, character2;

	void createWindow();

	// Test Function
	void runDrawing();
	
	void drawApplication();
	void drawSprite();

public:
	Render() {}

	void startApplication();
	
	void awaitScreen();
	void renderPlayer();
	void renderSecondPlayer();

	// Getters
	sf::RenderWindow* getWindow() { return window; }
};