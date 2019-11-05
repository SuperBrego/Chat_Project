#include "ApplicationFlow.h"

void ApplicationFlow::startUp() {

	printf("======== INICIALIZANDO ========\n");
	printf("Inicio de Aplicacao - Digite:\n- 1 para Servidor\n- 2 para Cliente\n- 0 para sair\n");
	printf("============ ============\n");
	std::cin >> function;
	while (function > 2 || function < 0 ) {
		printf("Inicio de Aplicacao - Digite um numero valido:\n- 1 para Servidor\n- 2 para Cliente\n0 - para sair\n");
		printf("============ ============\n");
		std::cin >> function;
	}

	if (function == 1) {
		startServer();
	}
	else if(function == 2) {
		startClient();
	}
	else {
		exit(1);
	}
}

void ApplicationFlow::startServer() {
	
	server = new Server();

}

void ApplicationFlow::startClient() {
	client = new Client();
}