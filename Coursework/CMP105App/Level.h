#pragma once

#include <SFML/Graphics.hpp>
#include "SFML/Network.hpp"
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/Collision.h"
#include "Framework/AudioManager.h"
#include "TileManager.h"
#include "EntityManager.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();

	void handleInput(float dt) override;
	void sendFunc(sf::TcpSocket& socket);
	void recFunc(sf::TcpSocket& socket);
	void sendMessage(sf::TcpSocket& socket);
	void recMessage(sf::TcpSocket& socket);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	

	// Default variables for level class.
	int posX;
	int posY;
	bool drawRange;
	bool pause;
	bool mute;
	bool send;
	TileManager tileManager;
	EntityManager entityManager;
	Input* input;
	sf::Sprite paused;
	sf::Texture pauseText;
};