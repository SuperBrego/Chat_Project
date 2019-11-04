#include <stdio.h>
#include <iostream>
#include <thread> 

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

// Headers
#include "ApplicationFlow.h"

ApplicationFlow* app;

int main(){
	
	app = new ApplicationFlow();
	app->startUp();

	return 0;
}
