#include "HowToPlay.h"

HTP::HTP(sf::RenderWindow* hwnd, Input* in, GameState* gs)
{
	window = hwnd;
	input = in;
	gameState = gs;

	if (!font.loadFromFile("font/arial.ttf")) 
	{
		
	}
	goLeft.setFont(font); 
	goLeft.setCharacterSize(20);
	goLeft.setFillColor(sf::Color::White);
	goLeft.setPosition(14, 558);
	goLeft.setString("Press Left to\ngo back");
	
	goRight.setFont(font); 
	goRight.setCharacterSize(20);
	goRight.setFillColor(sf::Color::White);
	goRight.setPosition(502, 558);
	goRight.setString("Press Right to\ncontinue");


	page = 1;

	page1Txt.loadFromFile("gfx/howToPlay1.png");
	page2Txt.loadFromFile("gfx/howToPlay2.png");
	page3Txt.loadFromFile("gfx/howToPlay3.png");

	page1.setTexture(page1Txt);
	page1.setPosition(0, 0);
	page2.setTexture(page2Txt);
	page2.setPosition(0, 0);
	page3.setTexture(page3Txt);
	page3.setPosition(0, 0);
}

HTP::~HTP()
{

}

void HTP::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::Right) && page <= 4)
	{
		input->setKeyUp(sf::Keyboard::Right);
		page += 1;
		return;
	}
	if (input->isKeyDown(sf::Keyboard::Left) && page >= 2)
	{
		input->setKeyUp(sf::Keyboard::Left);
		page -= 1;
		return;
	}
}

void HTP::update()
{
	if (page == 3)
	{
		goRight.setString("Press right to\nstart the game");
	}
	else
	{
		goRight.setString("Press Right to\ncontinue");
	}
}

void HTP::render()
{
	window->clear(sf::Color(5, 58, 105));
	switch (page)
	{
	case 1:window->draw(page1); break;
	case 2:window->draw(page2); break;
	case 3:window->draw(page3); break;
	//case 4: gameState->setCurrentState(State::LEVEL); break;
	}
	if (page > 1)
	{
		window->draw(goLeft);
	}
	window->draw(goRight);
	window->display();
}