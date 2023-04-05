#pragma once
#include "SFML/Graphics.hpp"
#include "Framework/Input.h"
#include "Framework/GameState.h"
class HTP
{
public:
	HTP(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~HTP();

	void handleInput();
	void update();
	void render();
private:
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

	int page;
	sf::Sprite page1;
	sf::Sprite page2;
	sf::Sprite page3;
	sf::Texture page1Txt;
	sf::Texture page2Txt;
	sf::Texture page3Txt;

	sf::Text goLeft;
	sf::Text goRight;
	sf::Font font;
};