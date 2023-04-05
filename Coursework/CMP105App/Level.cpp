#include "Level.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	// initialise game objects
	drawRange = false;
	aud->addMusic("sfx/gameSong.ogg", "gameBGM");
	aud->addSound("sfx/gameOver.ogg", "gameOver");
	aud->addSound("sfx/youWin.ogg", "win");
	pause = false;

	pauseText.loadFromFile("gfx/paused.png");
	paused.setTexture(pauseText);
	paused.setPosition(0, 0);

	bool mute = false;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	
	if (mute == false)
	{
		if (audio->getMusic()->getStatus() == sf::SoundSource::Stopped)
		{
			audio->playMusicbyName("gameBGM");
		}
	}
	
	posX = input->getMouseX();
	posY = input->getMouseY();
	if (input->isLeftMouseDown()) // place cannon
	{
		input->setLeftMouse(Input::MouseState::UP);
		entityManager.cannonSpawn(posX, posY);
		return;
	}
	if (input->isRightMouseDown()) // move cannon
	{
		entityManager.cannonMove(posX, posY);
		//input->setRightMouse(Input::MouseState::UP);
		return;
		
	}
	if (input->isKeyDown(sf::Keyboard::R)) //toggle range visibility
	{
		input->setKeyUp(sf::Keyboard::R);
		drawRange = !drawRange;
		return;
	}
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		pause = !pause;
		return;
	}
	if (input->isKeyDown(sf::Keyboard::M))
	{
		input->setKeyUp(sf::Keyboard::M);
		audio->stopAllMusic();
		mute = !mute;
		return;
	}
}

void Level::sendFunc(sf::TcpSocket& socket)
{
	entityManager.cannonSend(socket);
}

void Level::recFunc(sf::TcpSocket& socket)
{
	entityManager.cannonReceive(socket);
}

void Level::sendMessage(sf::TcpSocket& socket)
{
	entityManager.enemySend(socket);
}

void Level::recMessage(sf::TcpSocket& socket)
{
	entityManager.enemyReceive(socket);
}

// Update game objects
void Level::update(float dt)
{
	if(pause == false)
	{
		entityManager.enemySpawn();
		entityManager.enemyUpdate(dt);
		entityManager.cannonUpdate();
		entityManager.castleUpdate();
		entityManager.bulletUpdate(dt);
	}
	if (entityManager.halfAssedWinLosemanager() == 1)
	{
		audio->stopAllMusic();
		audio->playSoundbyName("win");
		gameState->setCurrentState(State::WIN);
	}
	if (entityManager.halfAssedWinLosemanager() == 2)
	{
		audio->stopAllMusic();
		audio->playSoundbyName("gameOver");
		gameState->setCurrentState(State::LOSE);
	}
}

// Render level
void Level::render()
{
	beginDraw();
	tileManager.render(window);
	entityManager.enemyRender(window);
	entityManager.cannonRender(window, drawRange);
	entityManager.castleRender(window);
	if (pause == true)
	{
		window->draw(paused);
	}	
	endDraw();
}

