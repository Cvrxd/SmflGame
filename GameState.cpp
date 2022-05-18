#include "stdafx.h" 
#include "GameState.h"

//Initialisation
inline void GameState::initKeybinds()
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

inline void GameState::initRenderTextures()
{
	this->renderTexture.create(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));
}

inline void GameState::initView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width), 
		static_cast<float>(this->stateData->gfxSettings->resolution.height)));

	this->view.setCenter(sf::Vector2f(this->stateData->gfxSettings->resolution.width / 2.f, this->stateData->gfxSettings->resolution.height / 2.f));
	//this->view.zoom(0.f);
}

inline void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

inline void GameState::initTextures()
{
	this->textures["PLAYER_SHEET"].loadFromFile("Textures/characters/player/test_sheet.png");
	this->textures["ENEMY_NIGHT_BORN"].loadFromFile("Textures/enemies/NightBorne.png");
	
}

inline void GameState::initPauseMenu()
{
	this->pauseMenu.addButton("CONTINUE", 400.f, -20.f,"Continue");
	this->pauseMenu.addButton("SKILLS", 550.f, 20.f, "Skills");
	this->pauseMenu.addButton("QUIT", 700.f, 40.f,"Quit");
}

inline void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "Shader error";
	}
}

inline void GameState::initPlayers()
{
}

void GameState::initEnemies()
{
	//
}

inline void GameState::initPlayerGUI()
{

}

inline void GameState::initTileMap()
{
	this->tileMap.loadFromFile("map/game_map.txt");
}

//Constructor
GameState::GameState(StateData* state_data)
	: State(state_data), skillMenuActive(false),
	pauseMenu(*this->window, this->stateData->font), //Pause menu 
	player(500,500, this->textures["PLAYER_SHEET"]), //Player
	playerGUI(this->player, this->font), // Player GUI
	skillsMenu(this->player, this->playerGUI,this->font, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)), // Skills menu
	tileMap(this->stateData->gridSize, 100, 100, "Textures/tiles/test22.jpg"), //Tile map
	test_enemy(NIGHTBORN, 1, 600, 600, this->textures["ENEMY_NIGHT_BORN"], &this->player)
{
	this->initRenderTextures();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();
	this->initTileMap();
}

GameState::~GameState()
{
}

// Funtions
inline void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player.getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
		std::floor(this->player.getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
	);

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x / this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y / this->stateData->gridSize);

	//World view
	
	/*if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}*/

}

//Pause menu update
inline void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu.isButtonPressed("QUIT"))
	{
		this->endState();
	}
	else if (this->pauseMenu.isButtonPressed("CONTINUE"))
	{
		this->unpausedState();
	}
	else if (this->pauseMenu.isButtonPressed("SKILLS"))
	{
		this->skillMenuActive = true;
	}
}

void GameState::updateEnemies(const float& dt)
{
	this->test_enemy.update(dt, mousPosView);
}

//Update functions
inline void GameState::updatePlayerInput(const float& dt)
{
	//check for keyboard key player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player.move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player.move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player.move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player.move(0.f, 1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		this->player.getStatsComponent()->gainEXP(1);
	}
}

inline void GameState::updateInput(const float& dt)
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
			this->skillMenuActive = false;
		}
	}
}

inline void GameState::updateTileMap(const float& dt)
{
	this->tileMap.update(&this->player, this->viewGridPosition, dt);
}

void GameState::update(const float& dt)
{
	this->updateMousePosition(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!this->paused) //Unpaused
	{
		this->updateView(dt);

		this->updateEnemies(dt);

		this->updatePlayerInput(dt);
		this->updateTileMap(dt);
		this->player.update(dt, this->mousPosView);

		//GUI UPDATE
		this->playerGUI.update(dt);
	} 
	else if (this->paused && this->skillMenuActive)
	{
		this->skillsMenu.update(this->mousePosWindow, dt);
	}
	else//Paused
	{
		this->pauseMenu.update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

inline void GameState::renderEnemies(sf::RenderTarget* target)
{
	this->test_enemy.render(this->renderTexture, &this->core_shader);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	//Set render texture
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);

	//tile map and player render
	//Using shader
	this->tileMap.renderGameState(this->renderTexture, this->player.getCenter(), &this->core_shader);

	this->renderEnemies(target);
	this->player.render(this->renderTexture, &this->core_shader);

	this->tileMap.renderAbove(this->renderTexture, this->player.getCenter(), &this->core_shader);

	//player GUI render
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI.render(this->renderTexture);

	if (this->paused && !this->skillMenuActive) //Pause menu render
	{
		this->pauseMenu.render(this->renderTexture);
	}
	else if(this->paused && this->skillMenuActive)
	{
		this->skillsMenu.render(this->renderTexture);
	}

	//Render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
