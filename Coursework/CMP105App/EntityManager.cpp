#include "EntityManager.h"
EntityManager::EntityManager()
{
	if (!healthFont.loadFromFile("font/arial.ttf"))
	{
		
	}
	healthText.setFont(healthFont);
	healthText.setCharacterSize(18);
	healthText.setFillColor(sf::Color::Red);
	healthText.setPosition(48, 614);
	
	waveText.setFont(healthFont);
	waveText.setCharacterSize(48);
	waveText.setFillColor(sf::Color::Red);
	waveText.setPosition(200, 48);

	spawnPoint = sf::Vector2f(80, 0);
	enemyText.loadFromFile("gfx/enemy.png"); 
	enemy2Text.loadFromFile("gfx/enemy2.png"); 
	enemy3Text.loadFromFile("gfx/enemy3.png"); 
	for (int i = 0; i < 6; i++)
	{
		enemies.push_back(Enemy());
		enemies[i].setAlive(false);
		enemies[i].setKilled(false); //killed variable is to stop enemies from respawning, as isAlive variable isnt enough   
		enemies[i].setTexture(&enemyText);
		enemies[i].setSpeed(40.f);
		enemies[i].setHealth(1);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		std::vector<Enemy> hello;
		hello.push_back(Enemy());
		messages.push_back(hello);
	}

	cannonText.loadFromFile("gfx/cannon.png");
	rangeText.loadFromFile("gfx/range.png");
	bullText.loadFromFile("gfx/bullet.png");
	for (int j = 0; j < 15; j++)
	{
		cannons.push_back(Cannon());
		cannons[j].setAlive(false);
		cannons[j].setTexture(&cannonText);
		cannons[j].setRotation(0.f);

		range.push_back(Range());
		range[j].setAlive(false);
		range[j].setTexture(&rangeText);

		bullets.push_back(Bullet());
		bullets[j].setAlive(false);
		bullets[j].setTexture(&bullText);
	}


	castleText.loadFromFile("gfx/castle.png");
	castle.setAlive(true);
	castle.setTexture(&castleText);
	castle.setPosition(240, 624);
	castle.setSize(sf::Vector2f(32, 32));
	castle.setCollisionBox(0, 0, 32, 32);
	castle.setOrigin(16, 16);

	audio.addSound("sfx/boom.ogg", "boom");

}

EntityManager::~EntityManager()
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////* ENEMY FUNCTIONS */////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void EntityManager::enemyArray(int wave[], int size)
{
	messages.clear();
	for (int i = 0; i < size; i++)
	{
		enemies.push_back(Enemy());
		enemies[i].setAlive(false);
		enemies[i].setKilled(false);
		switch(wave[i])
		{ case 1: 
			enemies[i].setSpeed(40.f);
			enemies[i].setTexture(&enemyText);
			enemies[i].setHealth(1);
			break;
		case 2:
			enemies[i].setSpeed(50.f);
			enemies[i].setTexture(&enemy2Text);
			enemies[i].setHealth(2);
			break;
		case 3:
			enemies[i].setSpeed(60.f);
			enemies[i].setTexture(&enemy3Text);
			enemies[i].setHealth(3);
			break;
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		std::vector<Enemy> hello;
		hello.push_back(Enemy());
		messages.push_back(hello);
	}
}

void EntityManager::enemySpawn()
{
	time = clock.getElapsedTime();
	for (int i = 0; i < enemies.size(); i++)
	{
		if (time.asSeconds() >= 1)
		{
			if (!enemies[i].isAlive() && enemies[i].getKilled() == false)
			{
				enemies[0].setAlive(false); //first enemy always spawns at the same time as the second for some reason??? really shoddy fix
				enemies[0].setKilled(true);
				enemies[i].setAlive(true);
				enemies[i].setPosition(spawnPoint);
				enemies[i].setVelocity(0, enemies[i].getSpeed());
				return; //<-- IMPORTANT BIT it stops all enemies spawning at once
			}
			clock.restart();
		}
	}
	if (enemiesKilled == enemies.size())
	{
		wave += 1;
		enemies.clear();
		switch (wave)
		{
		case 2: enemyArray(wave2, 8); break;
		case 3: enemyArray(wave3, 10); break;
		case 4: enemyArray(wave4, 12); break;
		case 5: enemyArray(wave5, 15); break;
		case 6: state.setCurrentState(State::WIN);
		}
		
		return;
	}
}


void EntityManager::enemyUpdate(float dt)
{
	std::string yeah = "Wave " + std::to_string(wave) + "/5";
	waveText.setString(yeah);
	enemiesKilled = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			enemies[i].update(dt);
			pathUpdate();
		}
		if (enemies[i].getKilled() == true)
		{
			enemiesKilled += 1;
		}
		switch (enemies[i].getHealth())
		{
		case 2: enemies[i].setTexture(&enemy2Text);
			enemies[i].setSpeed(50.f);
			break;
		case 1: enemies[i].setTexture(&enemyText);
			enemies[i].setSpeed(40.f);
			break;
		}
	}
	enemyDeathCheck();
}

void EntityManager::enemyDeathCheck()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			if (enemies[i].getPosition().x < 0)
			{
				enemies[i].setAlive(false);
				enemies[i].setKilled(true);

			}
			if (enemies[i].getPosition().x > 640)
			{
				enemies[i].setAlive(false);
				enemies[i].setKilled(true);
			}
			if (enemies[i].getPosition().y < -10)
			{
				enemies[i].setAlive(false);
				enemies[i].setKilled(true);
			}
			if (enemies[i].getPosition().y > 650)
			{
				enemies[i].setAlive(false);
				enemies[i].setKilled(true);
			}
			if (enemies[i].getHealth() <= 0)
			{
				enemies[i].setAlive(false);
				enemies[i].setKilled(true);
			}
		}
	}
}


void EntityManager::enemyRender(sf::RenderWindow* window)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			window->draw(enemies[i]);
		}
	}
}

void EntityManager::pathUpdate()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			for (int j = 0; j < 8; j++)
			{
				if (enemies[i].getPosition().x >= enemyPoints[0][j] 
					&& enemies[i].getPosition().y >= enemyPoints[1][j]
					&& enemies[i].getPosition().x < enemyPoints[0][j] + 3.1f
					&& enemies[i].getPosition().y < enemyPoints[1][j] + 3.1f) // checks if enemy has reached points in array
				{
					switch (j)
						// changes velocity at points defined in array, this allows the enemies to move along the path
					{
					case 0: enemies[i].setVelocity(enemies[i].getSpeed(), 0); break; 
					case 1: enemies[i].setVelocity(0, enemies[i].getSpeed()); break;
					case 2: enemies[i].setVelocity(-enemies[i].getSpeed(), 0); break;
					case 3: enemies[i].setVelocity(0, -enemies[i].getSpeed()); break;
					case 4: enemies[i].setVelocity(-enemies[i].getSpeed(), 0); break;
					case 5: enemies[i].setVelocity(0, enemies[i].getSpeed()); break;
					case 6: enemies[i].setVelocity(enemies[i].getSpeed(), 0); break;
					case 7: enemies[i].setVelocity(0, enemies[i].getSpeed()); break;
					}
					return;
				}
			}
		}
	}
}

void EntityManager::enemySend(sf::TcpSocket& socket)
{
	sf::Packet packet;

	//packet.clear();
	for (sf::Uint32 i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			if (enemies[i].getSentTime() < enemies[i].getTime()) //sends a packet every period 
			{
				packet.clear();
				int number = 2;
				packet << number << i << enemies[i].getPosition().x << enemies[i].getPosition().y << enemies[i].getVelocity().x << enemies[i].getVelocity().y << enemies[i].isAlive()
					<< enemies[i].getKilled() << wave;
				enemies[i].setSentTime(enemies[i].getSentTime() + sendRate);
				socket.send(packet);
			}
		}
	}
}

void EntityManager::enemyReceive(sf::TcpSocket& socket)
{
	sf::Packet packet;
	socket.receive(packet);
	sf::Uint32 eye;
	int number;
	float posx, posy;
	float velx, vely;
	int wavey;
	bool live, kill;
	if (packet >> number >> eye >> posx >> posy >> velx >> vely >> live >> kill >> wavey)
	{
		if (number == 2) //this is so the program knows the packet is an enemy
		{

		if (wavey == wave)
		{
			enemies[eye].setPosition(posx, posy);
			enemies[eye].setVelocity(velx, vely);
			enemies[eye].setAlive(live);
			enemies[eye].setKilled(kill);
			//enemies[eye].restartClock();

			sf::Vector2f getPredict = predictionFunction(eye);
			if (getPredict.x != 0.0f && getPredict.y != 0.0f)
			{
				float lerpX = enemies[eye].getPosition().x + 0.5f * (getPredict.x - enemies[eye].getPosition().x);
				float lerpY = enemies[eye].getPosition().y + 0.5f * (getPredict.y - enemies[eye].getPosition().y);

				enemies[eye].setPosition(lerpX, lerpY);
			}
			else
			{
				enemies[eye].setPosition(posx, posy);
			}
			messages[eye].push_back(enemies[eye]);

		}
		}

	}
	packet.clear();

}



/*void EntityManager::predictionFunction()
{
	for (int i = 0; i < messages.size(); i++)
	{
		if (messages[i].size() >= 3 && enemies[i].getTime() > sendRate) //making this 3 instead of 2 bc each array has an empty enemy at the start
		{
			Enemy& msg1 = messages[i][messages[i].size() - 1];
			Enemy& msg2 = messages[i][messages[i].size() - 2];
			float times = (msg1.getTime() - msg2.getTime());

			float speedX = (msg1.getPosition().x - msg2.getPosition().x) / times;
			float speedY = (msg1.getPosition().y - msg2.getPosition().y) / times;

			times = enemies[i].getTime() - msg1.getTime();

			float displaceX = speedX * times;
			float displaceY = speedY * times;

			float predictedX = (msg1.getPosition().x + displaceX);
			float predictedY = (msg1.getPosition().y + displaceY);

			float lerpX = enemies[i].getPosition().x + 0.5f * (predictedX - enemies[i].getPosition().x);
			float lerpY = enemies[i].getPosition().y + 0.5f * (predictedY - enemies[i].getPosition().y);

			enemies[i].setPosition(lerpX, lerpY);
		}
	}
}*/

sf::Vector2f EntityManager::predictionFunction(int i)
{
	if (messages[i].size() >= 3) //making this 3 instead of 2 bc each array has an empty enemy at the start
	{
			Enemy& msg1 = messages[i][messages[i].size() - 1];
			Enemy& msg2 = messages[i][messages[i].size() - 2];
			float times = (msg1.getTime() - msg2.getTime());

			float speedX = (msg1.getPosition().x - msg2.getPosition().x) / times;
			float speedY = (msg1.getPosition().y - msg2.getPosition().y) / times;

			float displaceX = speedX * times;
			float displaceY = speedY * times;

			float predictedX = (msg1.getPosition().x + displaceX);
			float predictedY = (msg1.getPosition().y + displaceY);

			return sf::Vector2f(predictedX, predictedY);
	}
	else {
		return sf::Vector2f(0.0f, 0.0f);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////*CANNON FUNCTIONS*//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void EntityManager::cannonSpawn(float x, float y)
{
	for (int i = 0; i < cannons.size(); i++)
	{
		if (!cannons[i].isAlive())
		{
			cannons[i].setAlive(true);
			cannons[i].setPosition(x, y);
			range[i].setAlive(true);
			range[i].setPosition(x, y);
			if (tileMan.collision(cannons[i]) == true) //if collision with path is detected, immediately despawn cannon
			{
				cannons[i].setAlive(false);
				range[i].setAlive(false);
			}
			return;
		}
	}
}

void EntityManager::cannonMove(float x, float y) //ITS CONTROLLABLE. CUT ME SOME SLACK
{
	for (int i = 0; i < cannons.size(); i++)
	{
		if (cannons[i].isAlive())
		{
			if(x >= (cannons[i].getPosition().x - 16) && x <= ((cannons[i].getPosition().x + cannons[i].getSize().x) -16)
				&& y >= (cannons[i].getPosition().y - 16) && y <= ((cannons[i].getPosition().y + cannons[i].getSize().y) - 16)) //checks if mouse is touching cannon
			{
				float posX = cannons[i].getPosition().x;
				float posY = cannons[i].getPosition().y;
				cannons[i].setPosition(x, y);
				range[i].setPosition(x, y);
				if (tileMan.collision(cannons[i]) == true) //if collision with path is detected, immediately return cannon to previous position
				{
					cannons[i].setPosition(posX, posY);
					range[i].setPosition(posX, posY);
				}
			}
		}
	}
}

void EntityManager::cannonUpdate()
{
	
	cannonTime = cannonClock.getElapsedTime();
	for (int i = 0; i < cannons.size(); i++)
	{
		if (cannonTime.asSeconds() > 1)
		{
			if (cannons[i].isAlive())
			{
				cannons[i].setRotation(0.f);
				float angle = cannonCollide(range[i],cannons[i]);
				cannons[i].rotate(angle); //angle now working; fixed it fixed it fixed it
			}cannonClock.restart();
		}
	}
}
	


float EntityManager::cannonCollide(GameObject go1, GameObject go2)
{
	for (int j = 0; j < enemies.size(); j++)
	{
		if(enemies[j].isAlive())
		{
		if (Collision::checkBoundingBox(&go1, &enemies[j]) == true)
		{
			float angle = collisionResponse(go2, enemies[j]);
			angle += 90;
			return angle;// cannon update calling this function then this function calling ANOTHER function is undoubtedly a mess, but without this only one tower would shoot at enemies rather than all of them
		}
		}
	}
}

void EntityManager::cannonRender(sf::RenderWindow* window, bool boolean)
{
	for (int i = 0; i < cannons.size(); i++)
	{
		if (cannons[i].isAlive())
		{
			if (boolean == true)
			{
				window->draw(range[i]);
			}
			bulletRender(window);
			window->draw(cannons[i]);
		}
	}
}

void EntityManager::cannonSend(sf::TcpSocket& socket)
{
	sf::Packet packet;

	for (sf::Uint32 i = 0; i < cannons.size(); i++)
	{
		if (cannons[i].isAlive())
		{
			int num = 1;
			packet.clear();
			packet << num << i << cannons[i].getPosition().x << cannons[i].getPosition().y << cannons[i].isAlive();
		}
	}
	socket.send(packet); //this entire function has been the bane of my existence. never again
}

void EntityManager::cannonReceive(sf::TcpSocket& socket)
{
	sf::Packet packet;
	socket.receive(packet);
	int number;
	float x, y;
	sf::Uint32 eye;
	bool live;
	if (packet >> number >> eye >> x >> y >> live)
	{
		if (number == 1) //this is so the program knows this packet is for the cannon. it likes to mix up packets
		{
		cannons[eye].setPosition(x, y);
		cannons[eye].setAlive(live);
		range[eye].setPosition(x, y);
		range[eye].setAlive(live);
		}
	}

	packet.clear();
}

float EntityManager::collisionResponse(GameObject go1, GameObject go2)
{
	sf::Vector2f centre1 = (go1.getPosition());
	sf::Vector2f centre2 = (go2.getPosition());

	//Adapted from https://en.sfml-dev.org/forums/index.php?PHPSESSID=6dhe0csqmn9deb43rq9ot4bdu5&topic=15099.msg106866#msg106866 
	float angle = (atan2((centre1.y - centre2.y), (centre1.x - centre2.x)) * 180 / 3.141); //finds angle the cannon should face by finding the difference in x and y between the cannon and the enemy
	if (angle < 0)
	{
		angle *= -1;	
	}
	float rotation = 0;
	//spawns bullet at cannon centre and sets velocity to move toward enemy
	bulletSpawn(go1.getPosition(), (centre1.x - centre2.x), (centre1.y - centre2.y));
	//I HATE ANGLES I HATE MATHS (rotates the cannon to face the enemy)
	if ((centre1.x - centre2.x) < 0 && (centre1.y - centre2.y) < 0)
	{
		rotation = 180 - angle; 
	}
	else if ((centre1.x - centre2.x) < 0 && (centre1.y - centre2.y) >= 0)
	{
		rotation = 90 - angle; 
	}
	else if ((centre1.x - centre2.x) >= 0 && (centre1.y - centre2.y) < 0)
	{
		rotation = 90 + angle; 
	}
	else if ((centre1.x - centre2.x) >= 0 && (centre1.y - centre2.y) >= 0)
	{
		rotation = 180 + angle;
	}
	return rotation;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////*BULLET FUNCTIONS*//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void EntityManager::bulletSpawn(sf::Vector2f cannonPosition, float diffX, float diffY)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i].isAlive())
		{
			bullets[i].setAlive(true);
			bullets[i].setPosition(cannonPosition);
			bullets[i].setVelocity(-diffX*7, -diffY*7);
			return;
		}
	}
}

void EntityManager::bulletUpdate(float dt)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].update(dt);
		}
	}
	bullDeathCheck();
}
void EntityManager::bullDeathCheck()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			if (bullets[i].getPosition().x < 0)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().x > 640)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y < -10)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y > 650)
			{
				bullets[i].setAlive(false);
			}
			for (int j = 0; j < enemies.size(); j++)
			{
				if (Collision::checkBoundingBox(&bullets[i], &enemies[j]) == true)
				{
					bullets[i].setAlive(false); 
					int currHealth = enemies[j].getHealth();
					enemies[j].setHealth(currHealth - 1);
				}
			}
		}
	}
}
void EntityManager::bulletRender(sf::RenderWindow* window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			window->draw(bullets[i]);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////* CASTLE FUNCTIONS*/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void EntityManager::castleUpdate()
{
	std::string health = "Base health: " + std::to_string(castleHealth) + "/25"; //these two lines output castle's health to screen 
	healthText.setString(health);

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			if (Collision::checkBoundingBox(&enemies[i], &castle))
			{
				audio.playSoundbyName("boom");
				enemies[i].setAlive(false);
				enemies[i].setKilled(true);
				castleHealth -= enemies[i].getHealth();
				return;
			}
		}
	}
	if (castleHealth <= 0)
	{
		
		state.setCurrentState(State::LOSE);
	}
}

void EntityManager::castleRender(sf::RenderWindow* window)
{
	window->draw(castle);
	window->draw(healthText);
	window->draw(waveText);
}

int EntityManager::halfAssedWinLosemanager()
{
	//imagine using pointers
	if (state.getCurrentState() == State::HOWTOPLAY)
	{
		return 0;
	}
	if (state.getCurrentState() == State::WIN)
	{
		return 1;

	}
	if (state.getCurrentState() == State::LOSE)
	{
		return 2;
	}
	//this doesnt actually work since restarting keeps win/lose state. not my problem though
}