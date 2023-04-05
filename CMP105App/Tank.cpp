#include "Tank.h"

Tank::Tank()
{
	setSize(sf::Vector2f(42, 42));
	setCollisionBox(0, 0, 42, 42);
	setOrigin(21, 21);
	setTime(0.0f);
}

Tank::~Tank()
{}

void Tank::update(float dt)
{
	timee += dt;
}

Barrel::Barrel()
{
	setSize(sf::Vector2f(12, 30));
	setCollisionBox(0, 0, 12, 30);
	setOrigin(6, 24);
}

Barrel::~Barrel()
{}


float Tank::getTime()
{
	return timee;
}

void Tank::setTime(float newTime)
{
	timee = newTime;
}

float Tank::getSentTime()
{
	return sentTime;
}

void Tank::setSentTime(float newTime)
{
	sentTime = newTime;
}