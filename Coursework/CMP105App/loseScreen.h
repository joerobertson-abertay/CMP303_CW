#pragma once
#include "SFML/Graphics.hpp"
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"

class LoseScreen
{
public:
	LoseScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~LoseScreen();

	void handleInput();
	void update();
	void render();
private:
	//using same variables as level class constructor
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

	sf::Sprite lose;
	sf::Texture loseText;
};
