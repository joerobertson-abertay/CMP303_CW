#include "CannonManager.h"
#include <iostream>
using namespace std;
CannonManager::CannonManager()
{
	cannonText.loadFromFile("gfx/cannon.png");
	for (int i = 0; i < 15; i++)
	{
		cannons.push_back(Cannon());
		cannons[i].setAlive(false);
		cannons[i].setTexture(&cannonText);
		cannons[i].setSize(sf::Vector2f(32, 32));
		cannons[i].setCollisionBox(0, 0, 32, 32);
	}
}

CannonManager::~CannonManager()
{

}

void CannonManager::spawn(int x,int y)
{
	for (int i = 0; i < cannons.size(); i++)
	{
		if (!cannons[i].isAlive())
		{
			cannons[i].setAlive(true);
			cannons[i].setPosition(x-16, y-16);
			std::cout << "Yeah" << endl;
			return;
		}
	}
}

void CannonManager::update(float dt)
{

}

void CannonManager::render(sf::RenderWindow* window)
{
	for (int i = 0; i < cannons.size(); i++)
	{
		if (cannons[i].isAlive())
		{
			window->draw(cannons[i]);
		}
	}
}