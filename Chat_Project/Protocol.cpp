#include "Protocol.h"

void Protocol::setClientName(std::string name) { clientName = name; }
void Protocol::setMessage(Message msg) { message = msg; }
void Protocol::setPlayerCharacter(Character data) { playerData = data; }

std::string Protocol::getclientName() { return clientName; }
Message Protocol::getMessage() { return message; }
Character Protocol::getPlayerData() { return playerData; }

void Protocol::toString() {

	std::string output = "";
	
	output += "==== Jogador: " + clientName + " ====\n";
	output += "== Acao: ";
	
	switch (message.getMessageType()) {
		case 1:
			output += "Ataque";
			break;
		case 2:
			output += "Bloquear";
		case 3:
			output += "Esquivar";
			break;
		default:
			output += "Server Reply";
			break;
	}
	output += " ==\n";
	if (message.getMessageType() > 2 || message.getMessageType() < 1) {
		output += "========";
	}
	else {
		output += "== Direcao: ";

		switch (message.getTypeCommand()) {
		case 0:
			output += "Cima";
			break;
		case 1:
			output += "Baixo";
		case 2:
			output += "Esquerda";
			break;
		case 3:
			output += "Direita";
			break;
		default:
			break;
		}

		output += " ==\n";
	}

	output += "\n";
	output += "=== Vida Total: " + std::to_string( playerData.getHealthPoints() ) + " ===\n";
	//output += message.getServerReply() + "\n";

	printf("%s\n", output.c_str());

}