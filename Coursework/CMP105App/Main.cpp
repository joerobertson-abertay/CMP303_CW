// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "MainMenu.h"
#include "WinScreen.h"
#include "loseScreen.h"
#include "HowToPlay.h"
#include "Server.h"
#include "Client.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "SFML/Network.hpp"
#include <thread>

void windowProcess(sf::RenderWindow* window, Input* in)
{
	// Handle window events.
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			break;
		case sf::Event::KeyPressed:
			// update input class
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			//update input class
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			//update input class
			in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setLeftMouse(Input::MouseState::DOWN);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::DOWN);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setLeftMouse(Input::MouseState::UP);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::UP);
			}
			break;
		default:
			// don't handle other events
			break;
		}
	}
}

int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(640, 640), "CMP105_Coursework", sf::Style::Titlebar | sf::Style::Close);

	sf::TcpSocket* sockServ = new sf::TcpSocket;
	sf::TcpSocket sockCli;
	sf::TcpListener listener;

	sockServ->setBlocking(false);
	//sockCli.setBlocking(false);
	listener.setBlocking(false);


	

	// Initialise input and level objects.
	AudioManager audioManager;
	Input input;
	GameState gameState;
	Level level(&window, &input, &gameState, &audioManager);
	MainMenu mainMenu(&window, &input, &gameState);
	WinScreen winScr(&window, &input, &gameState);
	LoseScreen loseScr(&window, &input, &gameState);
	HTP htp(&window, &input, &gameState);
	Server server(&window, &gameState, listener);
	Client client(&window, &gameState);

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;
	//Initialise state
	gameState.setCurrentState(State::MENU);
	// Game Loop
	while (window.isOpen())
	{
		//Process window events
		windowProcess(&window, &input);

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		// Call standard game loop functions (input, update and render)
		switch (gameState.getCurrentState()) //checks game state before calling functions
		{ 
			case (State::MENU):
				mainMenu.handleInput();
				mainMenu.update();
				mainMenu.render();
				break;
			case(State::SERVER):
				server.update(*sockServ, listener);
				server.render();
				break;
			case(State::CLIENT):
				client.update(sockCli);
				client.render();
				break;
			case (State::LEVEL_SERV):
				level.handleInput(deltaTime);
				level.update(deltaTime);
				level.sendFunc(*sockServ);
				level.recFunc(*sockServ);
				level.sendMessage(*sockServ);
				level.render();
				break;
			case (State::LEVEL_CLI):
				level.handleInput(deltaTime);
				level.update(deltaTime);
				level.sendFunc(sockCli);
				level.recFunc(sockCli);
				level.recMessage(sockCli);
				level.render();
				break;
			case(State::WIN):
				winScr.handleInput();
				winScr.update();
				winScr.render();
				break;
			case (State::LOSE):
				loseScr.handleInput();
				loseScr.update();
				loseScr.render();
				break;
			case(State::HOWTOPLAY):
				htp.handleInput();
				htp.update();
				htp.render();
				break;
		}
		/*if (gameState.menuToClient == true)
		{
			gameState.setCurrentState(State::CLIENT);
			std::thread clientThread(&Client::update);
			clientThread.detach();
			gameState.menuToClient = false;
		}*/
		// Update input class, handle pressed keys
		// Must be done last.
		input.update();
	}

}

