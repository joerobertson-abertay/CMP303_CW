#pragma once
#include "Framework/GameObject.h"
#include "SFML/Network.hpp"
class Cannon : public GameObject
{
public:
	Cannon();
	~Cannon();

	void update(float dt);

	void setTime(float newTime); //really just for messages
	float getTime();

	void setSentTime(float newTime);
	float getSentTime();

protected:
	float timee;
	float sentTime;
};

class Range : public GameObject
{
public:
	Range();
	~Range();
};
