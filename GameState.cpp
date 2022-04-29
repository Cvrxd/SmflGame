#include "stdafx.h" 
#include "GameState.h"

// Initialisation
//
// Keybinds init from ini
void GameState::initKeybinds()
{
	std::ifstream ifs("Configs/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key_value = "";

		while (ifs >> key >> key_value)
		{
			this->keybinds[key] = this->supportedKeys->at(key_value);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

//Textures initialisation
void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Textures/characters/player/test_sheet.png"))
	{
		throw("Could not load player texture");
		std::cout << "Fail";
	}
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	this->pauseMenu->addButton("CONTINUE", 400.f, -20.f,"Continue");
	this->pauseMenu->addButton("QUIT", 600.f, 40.f,"Quit");
}

//Init player 
void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
}

GameState::~GameState()
{
	delete player;
}

// Funtions

//Pause menu update
void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
	else if (this->pauseMenu->isButtonPressed("CONTINUE"))
	{
		this->unpausedState();
	}
}

//movement function and key board press
void GameState::updatePlayerInput(const float& dt)
{
	//check for keyboard key player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
	}
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpausedState();
		}

	}
}

// update GameState
void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!this->paused) //Unpaused
	{
		this->updatePlayerInput(dt);
		this->player->update(dt);
	} 
	else //Paused
	{
		this->pauseMenu->update(this->mousPosView);
		this->updatePauseMenuButtons();
	}
}

//render
void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	this->player->render(*target);

	if (this->paused) //Pause menu render
	{
		this->pauseMenu->render(*target);
	}
}
