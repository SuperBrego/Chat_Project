#include "Protocol.h"

void Protocol::toString() {

	std::string output = "";

	if (clientName != "Server") {

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
		output += "=== Vida Total: " + std::to_string(currentHealth) + " ===\n";
	}

	printf("%s\n", output.c_str());

}