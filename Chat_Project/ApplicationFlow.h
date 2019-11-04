// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <thread> 

#include "Client.h"
#include "Server.h"
#include "Protocol.h"
#include "Message.h"
#include "Render.h"

#pragma once

class ApplicationFlow {

	Render* render;
	int function;

	Client* client;
	Server* server;
	

public:
	ApplicationFlow() {
		render = new Render();
		//server = new Server();
		//clients = new Client[2];
	}
	~ApplicationFlow() {}

	void startUp();
	void startClient();
	void startServer();

};