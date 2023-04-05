#pragma once
#include "SFML/Graphics.hpp"
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include "EntityManager.h"
class MainMenu
{
public:
	MainMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~MainMenu();

	void handleInput();
	void update();
	void render();
private:
	//using same variables as level class constructor
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

	sf::Text titleText;
	sf::Font titleFont;
	sf::Text subText;
	sf::Text subText2;
	sf::Font subFont;
};