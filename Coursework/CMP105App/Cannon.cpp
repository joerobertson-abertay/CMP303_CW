#include "Cannon.h"

Cannon::Cannon()
{
	setSize(sf::Vector2f(32, 32));
	setCollisionBox(0, 0, 32, 32);
	setOrigin(16, 16);
	setTime(0.0f);
	timee = 0;
	sentTime = 0;
}

Cannon::~Cannon()
{}

void Cannon::update(float dt)
{
	timee += dt;
}

Range::Range()
{
	setSize(sf::Vector2f(96, 96));
	setCollisionBox(0, 0, 96, 96);
	setOrigin(48, 48);
}

Range::~Range()
{}


float Cannon::getTime()
{
	return timee;
}

void Cannon::setTime(float newTime)
{
	timee = newTime;
}

float Cannon::getSentTime()
{
	return sentTime;
}

void Cannon::setSentTime(float newTime)
{
	sentTime = newTime;
}