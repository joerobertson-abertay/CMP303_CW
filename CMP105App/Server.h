#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "Framework/GameState.h"
#include <iostream>
using namespace std;
class Server
{
public:
	Server(sf::RenderWindow* hwnd, GameState* gs, sf::TcpListener& listener);
	~Server();

	void update(sf::TcpSocket& socket, sf::TcpListener& listener);
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

};