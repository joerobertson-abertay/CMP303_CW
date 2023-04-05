#include "Bullet.h"

Bullet::Bullet()
{
	setSize(sf::Vector2f(14, 14));
	setCollisionBox(0, 0, 14, 14);
	setOrigin(7, 7);
}

Bullet::~Bullet()
{

}

void Bullet::update(float dt)
{
	move(velocity * dt);
}