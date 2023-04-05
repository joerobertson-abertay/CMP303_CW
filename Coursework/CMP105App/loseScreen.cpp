#include "loseScreen.h"

LoseScreen::LoseScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs)
{
	window = hwnd;
	input = in;
	gameState = gs;

	loseText.loadFromFile("gfx/loseScreen.png");
	lose.setPosition(0, 0);
	lose.setTexture(loseText);

	

}

LoseScreen::~LoseScreen()
{

}

void LoseScreen::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		input->setKeyUp(sf::Keyboard::Enter);
		gameState->setCurrentState(State::MENU);
		return;
	}
}

void LoseScreen::update()
{

}

void LoseScreen::render()
{
	window->draw(lose);
	window->display();
}