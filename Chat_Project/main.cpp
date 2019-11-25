#include <stdio.h>
#include <iostream>
#include <thread> 
#include <time.h>       /* time */


// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

// Headers
#include "ApplicationFlow.h"

ApplicationFlow* app;

int main(){

	srand(time(NULL));

	app = new ApplicationFlow();
	app->startUp();

	return 0;
}
