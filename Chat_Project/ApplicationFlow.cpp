#include "ApplicationFlow.h"

void ApplicationFlow::startUp() {

	printf("======== INICIALIZANDO ========");
	printf("Inicio de Aplicacao - Digite:\n- 1 para Servidor\n- 2 para Cliente\n");
	std::cin >> function;
	while (function != 1 && function != 2) {
		printf("Inicio de Aplicacao - Digite um numero valido:\n- 1 para Servidor\n- 2 para Cliente\n");
		std::cin >> function;
	}

	if (function == 1) {
		startServer();
	}
	else {
		startClient();
	}
}

void ApplicationFlow::startServer() {
	
	server = new Server();

}

void ApplicationFlow::startClient() {

}