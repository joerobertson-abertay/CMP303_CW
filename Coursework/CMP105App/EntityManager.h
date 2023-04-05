#pragma once
#include "Enemy.h"
#include "Cannon.h"
#include "TileManager.h"
#include "Bullet.h"


#include "SFML/Network.hpp"
#include "Framework/Collision.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
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

	void enemyArray(int wave[], int size);
	void enemySpawn();
	void enemyUpdate(float dt);
	void enemyDeathCheck();
	void enemyRender(sf::RenderWindow* window);
	void enemySend(sf::TcpSocket& socket);
	void enemyReceive(sf::TcpSocket& socket);
	void pathUpdate();

	void cannonSpawn(float x, float y);
	void cannonMove(float x, float y);
	void cannonUpdate();
	float cannonCollide(GameObject go1, GameObject go2);
	void cannonRender(sf::RenderWindow* window, bool boolean);
	void cannonSend(sf::TcpSocket& socket);
	void cannonReceive(sf::TcpSocket& socket);
	//void predictionFunction();
	sf::Vector2f predictionFunction(int i);

	void bulletSpawn(sf::Vector2f cannonPosition, float diffX, float diffY);
	void bulletUpdate(float dt);
	void bullDeathCheck();
	void bulletRender(sf::RenderWindow* window);

	void castleUpdate();
	void castleRender(sf::RenderWindow* window);
	
	float collisionResponse(GameObject go1, GameObject go2);
	const float enemyPoints[2][8] = {
		{80,528,528,399,399,111,111,239},
		{144,144,528,528,303,303,431,431}
	}; // points on the map to change direction at, first array is x position second array is y position

	int halfAssedWinLosemanager();

	//list of waves
	int wave2[9] = { 1,1,1,1,1,2,2,2,2 };
	int wave3[11] = { 1,1,1,2,2,1,1,2,2,2,2 };
	int wave4[13] = { 1,1,1,1,1,2,2,2,2,3,3,3,3 };
	int wave5[16] = { 1,1,1,1,2,2,2,3,3,3,2,2,2,3,3,3 };
	
protected:
	TileManager tileMan;
	std::vector<Enemy> enemies;
	std::vector<std::vector<Enemy>> messages;
	std::vector<Cannon> cannons;
	std::vector<Range> range;
	std::vector<Bullet> bullets;

	int enemiesKilled; //count enemies killed in the current wave
	int wave = 1;

	GameObject castle;
	int castleHealth = 25;
	sf::Vector2f spawnPoint;

	sf::Texture enemyText;
	sf::Texture enemy2Text;
	sf::Texture enemy3Text;
	sf::Texture cannonText;
	sf::Texture rangeText;
	sf::Texture bullText;
	sf::Texture castleText;

	sf::Clock clock;
	sf::Clock cannonClock;
	sf::Time time;
	sf::Time cannonTime; 
	float sendRate = 0.05f;

	sf::Font healthFont;
	sf::Text healthText;
	sf::Text waveText;


	sf::TcpListener listener;
	sf::IpAddress ip;
	AudioManager audio;
	GameState state;
}; 