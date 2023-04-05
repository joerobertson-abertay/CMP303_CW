#pragma once
#include "SFML/Graphics.hpp"
#include "Framework/Input.h"
#include "Framework/GameState.h"

class WinScreen
{
public:
	WinScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~WinScreen();

	void handleInput();
	void update();
	void render();
private:
	//using same variables as level class constructor
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

	sf::Sprite win;
	sf::Texture winText;
};