#pragma once
#include "Framework/GameObject.h"
#include "SFML/Network.hpp"
class Tank : public GameObject
{
public:
	Tank();
	~Tank();

	void update(float dt);

	void setTime(float newTime); //really just for messages
	float getTime();

	void setSentTime(float newTime);
	float getSentTime();

protected:
	float timee;
	float sentTime = 0.0f;
};

class Barrel : public GameObject
{
public:
	Barrel();
	~Barrel();
};
