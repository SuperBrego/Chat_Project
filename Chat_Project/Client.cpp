#include "Client.h"

Client::Client() {
	
	// Itens iniciais do cliente.
	currentHealth = 3;
	state = 0;
	direction = 0;
	endgame = false;
	client_name = "";

	// Se não conectou, sai.
	if (!connect()) {
		printf("==== Nao ha nenhum servidor rodando. Por favor entre em contato com o servidor e tente novamente. ====\n");
		system("pause");
	}
	// Se conectou, primeiro envia o login.
	else {

		char login[100];

		printf("==== Digite seu login: ====\n");
		std::cin >> login;
		
		// Nome do cliente para o Protocolo
		client_name = login;

		// Envia Login
		if (socket.send(login, 100) == sf::Socket::Done) {
		
			// Recebe retorno do servidor.
			char buffer[1024];
			std::size_t received = 0;
			socket.receive(buffer, sizeof(buffer), received);
			std::cout << buffer << std::endl;

			message = new Protocol();
			message->setClientName(client_name);
			message->setHealthPoints(currentHealth);

			// Inicia a aplicação
			startRender();
			run();
		}
	}

}

int Client::connect() {
	
	std::string ip;
	std::cout << "Digite o IP destino: \n";
	std::cin >> ip;

	sf::Time t1 = sf::seconds(1.f);
	sf::Socket::Status status = socket.connect(ip, 52000);
	
	if (status != sf::Socket::Done) {
		return 0;
	}

	return 1;
}

void Client::startRender() {

	render = new Render();
	render->setCurrentHearts(currentHealth);
	render->setCurrentState(state);
	render->setCurrentDirection(direction);
	render->startApplication();

}


void Client::run() {

	// Pronto para enviar mensagem.
	readySent = false;

	/* Loop da Aplicação */
	while (render->getWindow()->isOpen()) {

		sf::Event event;
		
		// Update da vida.
		message->setHealthPoints(currentHealth);

		// Poll Events
		while (render->getWindow()->pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				render->getWindow()->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				commandValidation();
			}
		}


		// Clear Screen
		render->getWindow()->clear(sf::Color::Black);

		// Draw Everything
		render->drawGame();

		// End the current frame
		render->getWindow()->display();

		// Caso a mensagem esteja pronta.
		if (readySent && !endgame) {

			// TCP socket:
			if (socket.send(message, sizeof(Protocol)) != sf::Socket::Done) {
				printf("Perdeu contato com servidor. Erro no cliente %s.\n", client_name.c_str());
			}

			// Recebe resposta do servidor
			Protocol* serverReply = new Protocol();
			std::size_t received = 0;
			sf::Socket::Status status = socket.receive(serverReply, sizeof(Protocol), received);

			printf("== Aguardando resposta do servidor ==\n");
			while (status != sf::Socket::Done) {}
			extractReply(serverReply);


			// Aguardar proxima mensagem
			readySent = false;
		}

	}

}

void Client::commandValidation() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		render->getWindow()->close();
		return;
	}

	// Atualizando a seleção
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (direction <= 0) direction = 0;
		else direction--;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (direction >= 3) direction = 3;
		else direction++;
	}

	// Atualiza Direcao
	render->setCurrentDirection(direction);

	// Atualizando os Itens
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (state == 2) {
			state = 0;
		}
		else state += 1;
	}
	
	// Atualiza Status
	render->setCurrentState(state);

	// Atualiza os itens do Render.
	render->Update();
	
	// Enviar comando
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		Message msg;

		msg.setMessageType(state);
		msg.setTypeCommand(direction);
		message->setMessage(msg);
		readySent = true;
		render->setWaitingServer(true);

	}

}

void Client::extractReply(Protocol* reply) {
	
	render->setWaitingServer(false);

	// Mensagem de Render
	if (reply->getMessage().getMessageType() == 1) {
		int renderPlural = reply->getMessage().getTypeCommand();

		if (renderPlural < 2) {

		}
		else {

		}
	}

	// Mensagem de Status
	else if (reply->getMessage().getMessageType() == 2) {

		int hp = reply->getHealthPoints();
		currentHealth = hp;

		// Atualiza vida no Render.
		render->setCurrentHearts(currentHealth);

		system("cls");
		printf("=== Player %s ===\n", this->client_name.c_str());
		printf("==== Pontos de Vida Total: ====\n");
		printf("===== %d =====\n", this->getHealthPoints());

	}
	// Mensagem de Fim de Jogo
	else if (reply->getMessage().getMessageType() == 3) {
		
		endgame = true;

		// Empate
		if (reply->getMessage().getTypeCommand() == 1) {
			// Render victory
			printf("=== Os dois jogadores perderam! Tivemos um empate! ===\n");
			render->setEndgame(1);
		}
		else {

			render->setEndgame(2);
			if (this->currentHealth > 0) {
				// Render victory
				printf("=== Player %s e vencedor deste jogo! ===\n", this->client_name.c_str());
			}
			else {
				// Render defeat
				printf("=== Player %s e foi derrotado desta vez! ===\n", this->client_name.c_str());
			}
		}

	}
}
