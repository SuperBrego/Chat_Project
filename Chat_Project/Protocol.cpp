#include "Protocol.h"

void Protocol::setClientName(char* name) {
	clientName = name;
}
void Protocol::setMessageType(int type) {
	message_type = type;
}
void Protocol::setDirection(int dir) {
	direction = dir;
}


char* Protocol::getclientName() {
	return clientName;
}
int Protocol::getMessageType() {
	return message_type;
}
int Protocol::getDirection() { 
	return direction;
}