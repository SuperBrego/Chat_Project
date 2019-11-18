#include <string>

#pragma once

class Message {
	int message_type; // 1 - Ataque, 2 - Bloquear, 3 - Esquivar
	int direction; // 0 - Cima, 1 - Baixo, 2 - Esquerda, 3 - Direita
	std::string serverReply;

public:

	void setMessageType(int type) {
		message_type = type;
	}
	void setDirection(int dir) {
		direction = dir;
	}

	void setServerReply(std::string str) {
		serverReply = str;
	}

	int getMessageType() {
		return message_type;
	}
	int getDirection() {
		return direction;
	}

	std::string getServerReply() {
		return serverReply;
	}
};