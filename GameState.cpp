#include "stdafx.h" 
#include "GameState.h"

// Initialisation

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

void GameState::initRenderTextures()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));
	this->view.setCenter(sf::Vector2f(this->stateData->gfxSettings->resolution.width / 2.f, this->stateData->gfxSettings->resolution.height / 2.f));
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Textures/characters/player/test_sheet.png"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD PLAYER TEEXTURE");
	
	}
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	this->pauseMenu->addButton("CONTINUE", 400.f, -20.f,"Continue");
	this->pauseMenu->addButton("QUIT", 600.f, 40.f,"Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Textures/tiles/test.png");
	this->tileMap->loadFromFile("map/game_map.txt");
}

//Constructor
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initRenderTextures();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	delete player;
	delete tileMap;
}

// Funtions
void GameState::updateView(const float& dt)
{
	this->view.setCenter(this->player->getPosition());
}

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

void GameState::update(const float& dt)
{
	this->updateMousePosition(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!this->paused) //Unpaused
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		this->player->update(dt);
	} 
	else //Paused
	{
		this->pauseMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->setView(this->view);
	this->tileMap->render(*target);
	this->player->render(*target);

	if (this->paused) //Pause menu render
	{
		target->setView(this->window->getDefaultView());
		this->pauseMenu->render(*target);
	}


}
