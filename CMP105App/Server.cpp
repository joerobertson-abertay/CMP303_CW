#include "Server.h"

Server::Server(sf::RenderWindow* hwnd, GameState* gs, sf::TcpListener& listener)
{
	window = hwnd;
	gameState = gs;
	if (!titleFont.loadFromFile("font/arial.ttf")) //checks if font is loaded correctly
	{

	}
	titleText.setFont(titleFont); //setting up Title Text, game name
	titleText.setCharacterSize(48);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(70, 240);
	titleText.setString("Waiting for connection...");

	if (listener.listen(55001) != sf::Socket::Done)
	{
		return;
	}
}

Server::~Server()
{

}

void Server::update(sf::TcpSocket& socket, sf::TcpListener& listener)
{
	titleText.setString("Searching for client...");
	// bind the listener to a port
	status = listener.accept(socket);
	// accept a new connection
	if (status == sf::Socket::Done)
	{	
		gameState->setCurrentState(State::LEVEL_SERV);
	}

}

void Server::render()
{
	window->clear(sf::Color(5, 58, 105));
	window->draw(titleText);

	window->display();
}