#pragma once
#include "Framework/GameObject.h"

class Enemy:public GameObject
{
public:
	Enemy();
	~Enemy();

	void update(float dt) override;

	void setKilled(bool kill);
	bool getKilled();

	void setSpeed(float newspeed);
	float getSpeed();

	void setHealth(int newhealth);
	int getHealth();

	void setTime(float newTime); //really just for messages
	float getTime();
	
	void setSentTime(float newTime); 
	float getSentTime();

protected:
	bool isKilled;
	sf::Texture enemyText;
	float speed;
	int health;
	float timee;
	float sentTime;
};