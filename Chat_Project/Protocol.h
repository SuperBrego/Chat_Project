#include <stdio.h>
#include <iostream>

#include "Message.h"

#pragma once

class Protocol {

	char* clientName;
	int message_type; // 1 - Ataque, 2 - Bloquear, 3 - Esquivar
	int direction; // 0 - Cima, 1 - Baixo, 2 - Esquerda, 3 - Direita

public:
	Protocol() {};
	~Protocol() {};

	void setClientName(char* name);
	void setMessageType(int type);
	void setDirection(int dir);

	char* getclientName();
	int getMessageType();
	int getDirection();
	
	void toString();

};
