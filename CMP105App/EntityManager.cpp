#include "EntityManager.h"
EntityManager::EntityManager()
{


	tankText.loadFromFile("gfx/blueTank.png");
	tank2Text.loadFromFile("gfx/redTank.png");
	barrelText.loadFromFile("gfx/blueBarrel.png");
	barrel2Text.loadFromFile("gfx/redBarrel.png");
	for (int j = 0; j < 2; j++)
	{
		tanks.push_back(Tank());

		barrels.push_back(Barrel());
	}
	tanks[0].setAlive(true);
	tanks[0].setPosition(160, 240);
	tanks[0].setTexture(&tankText);
	tanks[0].setRotation(0.f);

	barrels[0].setAlive(true);
	barrels[0].setTexture(&barrelText);
	barrels[0].setPosition(160, 240);
	barrels[0].setRotation(0.f);

	tanks[1].setAlive(true);
	tanks[1].setPosition(480, 320);
	tanks[1].setTexture(&tank2Text);
	tanks[1].setRotation(0.f);

	barrels[1].setAlive(true);
	barrels[1].setTexture(&barrel2Text);
	barrels[1].setPosition(480, 320);
	barrels[1].setRotation(0.f);

	for (int i = 0; i < tanks.size(); i++)
	{
		std::vector<Tank> hello;
		hello.push_back(Tank());
		messages.push_back(hello);
	}

	diffX = 0;
	diffY = 0;
}

EntityManager::~EntityManager()
{

}

sf::Vector2f EntityManager::predictionFunction(int i)
{
	if (messages[i].size() >= 3) 
	{
		Tank& msg1 = messages[i][messages[i].size() - 1];
		Tank& msg2 = messages[i][messages[i].size() - 2];
		float times = (msg1.getTime() - msg2.getTime());

		float speedX = (msg1.getPosition().x - msg2.getPosition().x) / times;
		float speedY = (msg1.getPosition().y - msg2.getPosition().y) / times;

		float displaceX = speedX * times;
		float displaceY = speedY * times;

		float predictedX = (msg1.getPosition().x + displaceX);
		float predictedY = (msg1.getPosition().y + displaceY);

		messages[i].erase(messages[i].begin());
		return sf::Vector2f(predictedX, predictedY);
	}
	else {
		return sf::Vector2f(0.0f, 0.0f);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////*CANNON FUNCTIONS*//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void EntityManager::tankMove(float x, float y, float rotation, int i, float dt) //ITS CONTROLLABLE. CUT ME SOME SLACK
{
	tanks[i].move(sf::Vector2f(x, y) * dt);
	tanks[i].setRotation(rotation);
	barrels[i].move(sf::Vector2f(x, y) * dt);
	if (tileMan.collision(tanks[i]) == true) //if collision with path is detected, immediately return cannon to previous position
	{
		tanks[i].move(sf::Vector2f(-x, -y)*dt);
		barrels[i].move(sf::Vector2f(-x, -y) * dt);
	}
}

void EntityManager::tankUpdate(float x, float y, int i, float dt)
{
	tanks[0].update(dt);
	tanks[1].update(dt);
	float angle = tankCollide(barrels[i], x, y);
	barrels[i].setRotation(angle); //angle now working; fixed it fixed it fixed it
}



float EntityManager::tankCollide(GameObject go1, float x, float y)
{
	
	float angle = collisionResponse(go1, x,y);
	return angle;// cannon update calling this function then this function calling ANOTHER function is undoubtedly a mess, but without this only one tower would shoot at enemies rather than all of them
		
}

void EntityManager::tankRender(sf::RenderWindow* window)
{
	for (int i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].isAlive())
		{
			window->draw(tanks[i]);
			window->draw(barrels[i]);
		}
	}
}

void EntityManager::tankSend(sf::TcpSocket& socket, int i)
{
	sf::Packet packet;

	if (tanks[i].isAlive())
	{
		if (tanks[i].getSentTime() < tanks[i].getTime()) //sends a packet every period 
		{
			packet.clear();
			packet << i << tanks[i].getPosition().x << tanks[i].getPosition().y << tanks[i].getRotation() << barrels[i].getRotation();
			tanks[i].setSentTime(tanks[i].getSentTime() + sendRate);
			socket.send(packet); //this entire function has been the bane of my existence. never again
		}
	}
}

void EntityManager::tankReceive(sf::TcpSocket& socket)
{
	sf::Packet packet;
	socket.receive(packet);

	float x, y; //position
	sf::Uint32 playNum; //iterator
	float tankRot, barrelRot; // tank rotation and barrel rotation
	if (packet >> playNum >> x >> y >> tankRot >> barrelRot)
	{
			tanks[playNum].setPosition(x, y);
			tanks[playNum].setRotation(tankRot);
			barrels[playNum].setPosition(x, y);
			barrels[playNum].setRotation(barrelRot);

			sf::Vector2f getPredict = predictionFunction(playNum);
			if (getPredict.x != 0.0f && getPredict.y != 0.0f)
			{
				float lerpX = tanks[playNum].getPosition().x + 0.5f * (getPredict.x - tanks[playNum].getPosition().x);
				float lerpY = tanks[playNum].getPosition().y + 0.5f * (getPredict.y - tanks[playNum].getPosition().y);

				tanks[playNum].setPosition(lerpX, lerpY);
				barrels[playNum].setPosition(lerpX, lerpY);
			}
			else
			{
				tanks[playNum].setPosition(x, y);
				barrels[playNum].setPosition(x, y);
			}
			messages[playNum].push_back(tanks[playNum]);
	}

	packet.clear();
}

float EntityManager::collisionResponse(GameObject go1, float x, float y)
{
	sf::Vector2f centre1 = (go1.getPosition());
	sf::Vector2f centre2 = (sf::Vector2f(x, y));

	//Adapted from https://en.sfml-dev.org/forums/index.php?PHPSESSID=6dhe0csqmn9deb43rq9ot4bdu5&topic=15099.msg106866#msg106866 
	float angle = (atan2((centre1.y - centre2.y), (centre1.x - centre2.x)) * 180 / 3.141); //finds angle the cannon should face by finding the difference in x and y between the cannon and the enemy
	
	float rotation = angle - 90;
	//spawns bullet at cannon centre and sets velocity to move toward enemy
	diffX = (centre1.x - centre2.x);
	diffY = (centre1.y - centre2.y);
	
	return rotation;
}