#include <SFML/Graphics.hpp>

#pragma once

class Character {
	int health_points = 3;
	std::string sprite_path = "";

public:
	Character() { health_points = 3; }
	void takeDamage() { health_points--; }
	void recoverDamage() { health_points++; }

	int getHealthPoints() { return health_points; }
	std::string getSpritePath() { return sprite_path; }
};