#include "WinScreen.h"

WinScreen::WinScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs)
{
	window = hwnd;
	input = in;
	gameState = gs;

	winText.loadFromFile("gfx/winScreen.png");
	win.setPosition(0, 0);
	win.setTexture(winText);
}

WinScreen::~WinScreen()
{
	
}

void WinScreen::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		input->setKeyUp(sf::Keyboard::Enter);
		gameState->setCurrentState(State::MENU);
		return;
	}
}

void WinScreen::update()
{

}

void WinScreen::render()
{
	window->draw(win);
	window->display();
}