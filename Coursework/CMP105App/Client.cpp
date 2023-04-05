#include "Client.h"

Client::Client(sf::RenderWindow* hwnd, GameState* gs)
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
	titleText.setString("Searching for server...");

	ip = sf::IpAddress::getLocalAddress();



}

Client::~Client()
{

}

void Client::update(sf::TcpSocket& socket)
{
	status = socket.connect(ip, 55001, sf::seconds(30));
	titleText.setString("Searching for server");
	if (status != sf::Socket::Done)
	{
		return;
	}
	

	titleText.setString("Server found...");
	gameState->setCurrentState(State::LEVEL_CLI);
}

void Client::render()
{
	window->clear(sf::Color(5, 58, 105));
	window->draw(titleText);

	window->display();
}