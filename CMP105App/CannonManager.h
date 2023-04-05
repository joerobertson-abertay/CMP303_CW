#pragma once
#include "Cannon.h"
class CannonManager : public GameObject
{
public:
	CannonManager();
	~CannonManager();

	void spawn(int x, int y);
	void update(float dt);
	void render(sf::RenderWindow* window);

private:
	
};