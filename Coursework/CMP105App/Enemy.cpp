#include "Enemy.h"

Enemy::Enemy()
{	
	setSize(sf::Vector2f(24.f, 24.f));
	setCollisionBox(sf::FloatRect(0, 0, 24, 24));
	setOrigin(12, 12);
	timee = 0;
	sentTime = 0;
}

Enemy::~Enemy()
{

}

void Enemy::update(float dt)
{
	timee += dt;
	move(velocity * dt);
}

bool Enemy::getKilled()
{
	return isKilled;
}

void Enemy::setKilled(bool kill)
{
	isKilled = kill;
}

float Enemy::getSpeed()
{
	return speed;
}

void Enemy::setSpeed(float newspeed)
{
	speed = newspeed;
}

int Enemy::getHealth()
{
	return health;
}

void Enemy::setHealth(int newHealth)
{
	health = newHealth;
}

float Enemy::getTime()
{
	return timee; 
}

void Enemy::setTime(float newTime)
{
	timee = newTime;
}

float Enemy::getSentTime()
{
	return sentTime;
}

void Enemy::setSentTime(float newTime)
{
	sentTime = newTime;
}