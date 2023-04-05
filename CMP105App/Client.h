#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "Framework/GameState.h"
class Client
{
public:
	Client(sf::RenderWindow* hwnd, GameState* gs);
	~Client();

	void update(sf::TcpSocket& socket);
	void render();
private:

	//using same variables as level class constructor
	sf::RenderWindow* window;
	GameState* gameState;

	sf::Text titleText;
	sf::Text subtext;

	sf::Font titleFont;
	sf::Font subFont;

	sf::Socket::Status status;
	sf::IpAddress ip;

};