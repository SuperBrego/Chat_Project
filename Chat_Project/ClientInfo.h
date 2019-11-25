#include <SFML\Network.hpp>
#include "Character.h"

#pragma once

class ClientInfo {

	sf::TcpSocket* socket;
	std::string login;
	Character* data;

public:
	
	void setSocket(sf::TcpSocket* sk) { socket = sk; }
	void setLogin(std::string lg) { login = lg; }
	void setData(Character clientData) {
		data = new Character();
		data->setHealthPoints(clientData.getHealthPoints());
	}
	
	sf::TcpSocket* getSocket() { return socket; }
	std::string getLogin() { return login; }
	Character* getPlayerData() { return data; }


};
