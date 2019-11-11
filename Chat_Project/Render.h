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

public:
	void startApplication();
	void drawApplication();
	void drawSprite();

	// Getters
	sf::RenderWindow* getWindow() { return window; }
};