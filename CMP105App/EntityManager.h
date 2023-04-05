#pragma once
#include "Tank.h"
#include "TileManager.h"
#include "Bullet.h"


#include "SFML/Network.hpp"
#include "Framework/Collision.h"
#include "Framework/AudioManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <cmath>
#include <cstdlib>
class EntityManager
{
public:
	EntityManager();
	~EntityManager();


	void tankMove(float x, float y, float rotation, int i, float dt);
	void tankUpdate(float x, float y, int i, float dt);
	float tankCollide(GameObject go1, float x, float y);
	void tankRender(sf::RenderWindow* window);
	void tankSend(sf::TcpSocket& socket, int i);
	void tankReceive(sf::TcpSocket& socket);
	//void predictionFunction();
	sf::Vector2f predictionFunction(int i);

	float collisionResponse(GameObject go1, float x, float y);

	void setPlayerNum(int number) { playerNumber = number; };
	int getPlayerNum() { return playerNumber; };

protected:
	TileManager tileMan;
	std::vector<std::vector<Tank>> messages;
	std::vector<Tank> tanks;
	std::vector<Barrel> barrels;


	sf::Texture tankText;
	sf::Texture tank2Text;
	sf::Texture barrelText;
	sf::Texture barrel2Text;

	float sendRate = 0.05f;
	float diffX, diffY;
	int playerNumber;

	sf::TcpListener listener;
	sf::IpAddress ip;
	AudioManager audio;
};