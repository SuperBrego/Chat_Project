#include "Protocol.h"

void Protocol::setClientName(std::string name) {
	clientName = name;
}
void Protocol::setMessageType(int type) {
	message_type = type;
}
void Protocol::setDirection(int dir) {
	direction = dir;
}


std::string Protocol::getclientName() {
	return clientName;
}
int Protocol::getMessageType() {
	return message_type;
}
int Protocol::getDirection() { 
	return direction;
}

void Protocol::toString() {

	std::string output = "";
	
	output += "==== Jogador: " + clientName + " ====\n";
	output += "== Acao: ";
	
	switch (message_type) {
		case 1:
			output += "Ataque";
			break;
		case 2:
			output += "Bloquear";
		case 3:
			output += "Esquivar";
			break;
		default:
			break;
	}
	output += " ==\n";
	if (message_type == 3) {
		output += "========";
	}
	else {
		output += "== Direcao: ";

		switch (direction) {
		case 0:
			output += "Cima";
			break;
		case 1:
			output += "Bloquear";
		case 2:
			output += "Esquivar";
			break;
		case 3:
			output += "Esquivar";
			break;
		default:
			break;
		}

		output += "==\n";
	}

	printf("%s\n", output.c_str());

}