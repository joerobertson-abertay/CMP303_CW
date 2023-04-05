#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs)
{
	window = hwnd;
	input = in;
	gameState = gs;

	if (!titleFont.loadFromFile("font/arial.ttf")) //checks if font is loaded correctly
	{

	}
	titleText.setFont(titleFont); //setting up Title Text, game name
	titleText.setCharacterSize(64);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(20, 240);
	titleText.setString("CMP303 Coursework");

	subText.setFont(titleFont); //setting up text that tells player to set up server
	subText.setCharacterSize(24);
	subText.setFillColor(sf::Color::White);
	subText.setPosition(135, 420);
	subText.setString("Press Enter to wait for connection");

	subText2.setFont(titleFont); //setting up text that tells player to connect to server
	subText2.setCharacterSize(24);
	subText2.setFillColor(sf::Color::White);
	subText2.setPosition(98, 460);
	subText2.setString("Press Space to connect to another player");
}

MainMenu::~MainMenu()
{

}

void MainMenu::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		input->setKeyUp(sf::Keyboard::Enter);
		gameState->setCurrentState(State::SERVER); //if enter is pressed, changes game state to server

	}
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		input->setKeyUp(sf::Keyboard::Space);
		gameState->setCurrentState(State::CLIENT); //if space is pressed, changes game state to client

	}
}

void MainMenu::update()
{

}

void MainMenu::render()
{
	window->clear(sf::Color(5, 58, 105));
	window->draw(titleText);
	window->draw(subText);
	window->draw(subText2);

	window->display();
}