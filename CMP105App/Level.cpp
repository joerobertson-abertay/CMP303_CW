#include "Level.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;


	bool mute = false;
}

Level::~Level()
{

}
void Level::setPlayerNumber(int i)
{
	entityManager.setPlayerNum(i);
}
// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::D)) // move cannon
	{
		switch (entityManager.getPlayerNum())
		{
		case 0:	entityManager.tankMove(200, 0, 90, 0, dt); break;
		case 1:	entityManager.tankMove(200, 0, 90, 1, dt); break;
		}
		
		return;

	}
	if (input->isKeyDown(sf::Keyboard::A)) // move cannon
	{
		switch (entityManager.getPlayerNum())
		{
		case 0:	entityManager.tankMove(-200, 0, 270, 0,dt); break;
		case 1:	entityManager.tankMove(-200, 0, 270, 1,dt); break;
		}
		return;

	}
	if (input->isKeyDown(sf::Keyboard::W)) // move cannon
	{
		switch (entityManager.getPlayerNum())
		{
		case 0:	entityManager.tankMove(0, -200, 0, 0,dt); break;
		case 1:	entityManager.tankMove(0, -200, 0, 1, dt); break;
		}
		return;

	}
	if (input->isKeyDown(sf::Keyboard::S)) // move cannon
	{
		switch (entityManager.getPlayerNum())
		{
		case 0:	entityManager.tankMove(0, 200, 0, 0, dt); break;
		case 1:	entityManager.tankMove(0, 200, 0, 1, dt); break;
		}
		return;

	}
}

void Level::sendFunc(sf::TcpSocket& socket)
{
	entityManager.tankSend(socket, entityManager.getPlayerNum());
}

void Level::recFunc(sf::TcpSocket& socket)
{
	entityManager.tankReceive(socket);
}
// Update game objects
void Level::update(float dt)
{
	float posX = sf::Mouse::getPosition(*window).x;
	float posY = sf::Mouse::getPosition(*window).y;
	entityManager.tankUpdate(posX,posY,entityManager.getPlayerNum(),dt);
}

// Render level
void Level::render()
{
	beginDraw();
	tileManager.render(window);
	entityManager.tankRender(window);
	endDraw();
}

