// Game State Class
// Simple game state controller. enum lists possible game states (can be modified), tracks and updates the current state
// @author Paul Robertson

#pragma once

// Possible states. This enum can be modified to add additional states as required.
enum class State { MENU, LEVEL_SERV, LEVEL_CLI, SERVER, CLIENT };

class GameState
{
public:
	// Set the current state
	void setCurrentState(State s);
	// Returns the current state.
	State getCurrentState();

	void setmenuToServer() { menuToServer = true; }
	void setmenuToClient() { menuToClient = true; }
	bool menuToServer;
	bool menuToClient;

protected:
	State currentState;
};