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
	this->font.loadFromFile("Fonts/Greybeard.ttf");
}

inline void GameState::initTextures()
{
	this->textures["PLAYER_SHEET"].loadFromFile("Textures/characters/player/test_sheet.png");

	//Monsters
	this->textures["ENEMY_NIGHT_BORN"].loadFromFile("Textures/enemies/boses/NightBorne.png");
	this->textures["ENEMY_MIMIC"].loadFromFile("Textures/enemies/mele/mimic.png");
	this->textures["ENEMY_FIRE_DEMON"].loadFromFile("Textures/enemies/boses/fire_demon.png");
	this->textures["ENEMY_BRINGER_OF_DEATH"].loadFromFile("Textures/enemies/mele/bringer_of_death.png");
	this->textures["ENEMY_NOMAND"].loadFromFile("Textures/enemies/mele/nomand.png");

	//Humans
	this->textures["ENEMY_KNIGHT1"].loadFromFile("Textures/enemies/mele/knight1.png");
	this->textures["ENEMY_HUNTRESS"].loadFromFile("Textures/enemies/mele/huntress.png");
	this->textures["ENEMY_SAMURAI"].loadFromFile("Textures/enemies/boses/samurai.png");
	this->textures["ENEMY_MARTIAL_HERO1"].loadFromFile("Textures/enemies/mele/martial_hero1.png");
	this->textures["ENEMY_MARTIAL_HERO2"].loadFromFile("Textures/enemies/mele/martial_hero2.png");

	//Mages
	this->textures["ENEMY_DARK_MAGE"].loadFromFile("Textures/enemies/mages/dark_mage.png");
	this->textures["ENEMY_FIRE_MAGE"].loadFromFile("Textures/enemies/mages/fire_mage.png");

	//Destroying enemies
	this->textures["ENEMY_FIRE_SKULL"].loadFromFile("Textures/enemies/destroying/fire-skull.png");
}

inline void GameState::initPauseMenu()
{
	this->pauseMenu.addButton("CONTINUE", 350.f, -20.f,"Continue");
	this->pauseMenu.addButton("SKILLS", 500.f, 20.f, "Skills");
	this->pauseMenu.addButton("ITEMS", 650.f, 20.f, "items");
	this->pauseMenu.addButton("QUIT", 800.f, 40.f,"Quit");
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

inline void GameState::initEnemies()
{
	this->bosses.reserve(3);
	this->bosses.emplace_back(BossType::SAMURAI, 1, 100, 900, this->textures["ENEMY_SAMURAI"], &this->player, this->enemiesSounds);

	this->meleEnemies.reserve(3);
	//this->meleEnemies.emplace_back(MeleEnemyType::MIMIC, 5, 700, 700, this->textures["ENEMY_MIMIC"], &this->player, this->enemiesSounds);
	//this->meleEnemies.emplace_back(MeleEnemyType::NOMAND, 5, 700, 700, this->textures["ENEMY_NOMAND"], &this->player, this->enemiesSounds);
	//this->meleEnemies.emplace_back(MeleEnemyType::BRINGER_OF_DEATH, 5, 700, 700, this->textures["ENEMY_BRINGER_OF_DEATH"], &this->player, this->enemiesSounds);

	this->mageEnemies.reserve(2);
	//this->mageEnemies.emplace_back(MageEnemyType::FIRE_MAGE, 1, 400, 400, this->textures["ENEMY_FIRE_MAGE"], &this->player, this->enemiesSounds);

	this->destroyingEnemies.reserve(2);
	//this->destroyingEnemies.emplace_back(DestroyingEnemyType::FIRE_SKULL, 1, 0, 0, this->textures["ENEMY_FIRE_SKULL"], &this->player, this->enemiesSounds);
}

inline void GameState::initPlayerGUI()
{
	this->player.setPlayerGUI(this->playerGUI);
}

inline void GameState::initTileMap()
{
	this->tileMap.loadFromFile("map/game_map.txt");
}

inline void GameState::initSounds()
{
}

//Constructor
GameState::GameState(StateData* state_data)
	: State(state_data), skillMenuActive(false),
	pauseMenu(*this->window, this->stateData->font), //Pause menu 
	player(500,500, this->textures["PLAYER_SHEET"], this->font, this->isBuffed), //Player
	playerGUI(this->player, this->font), // Player GUI
	skillsMenu(this->player, this->playerGUI,this->font, this->guiSounds,static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)), // Skills menu
	itemsMenu(this->player, this->playerGUI, this->font, this->guiSounds, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)), // items menu
	tileMap(this->stateData->gridSize, 100, 100, "Textures/tiles/test22.jpg") //Tile map
{
	this->initRenderTextures();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initSounds();
	this->initEnemies();
	this->initShaders();
	this->initTileMap();
	this->initPlayerGUI();
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
		this->pauseMenu.playClickSound();

		this->unpausedState();
	}
	else if (this->pauseMenu.isButtonPressed("SKILLS"))
	{
		this->pauseMenu.playClickSound();

		this->skillMenuActive = true;
	}
	else if (this->pauseMenu.isButtonPressed("ITEMS"))
	{
		this->pauseMenu.playClickSound();

		this->itemsMenuActive = true;
	}
}

inline void GameState::updateEnemies(const float& dt)
{
	for (auto& el : this->bosses)
	{
		if (!el.dead())
		{
			el.update(dt, this->mousPosView);
		}
	}
	for (auto& el : this->meleEnemies)
	{
		if (!el.dead())
		{
			el.update(dt, this->mousPosView);
		}
	}
	for (auto& el : this->mageEnemies)
	{
		if (!el.dead())
		{
			el.update(dt, this->mousPosView);
		}
	}
	for (auto& el : this->destroyingEnemies)
	{
		if (!el.dead())
		{
			el.update(dt, this->mousPosView);
		}
	}
}

//Update functions
inline void GameState::updatePlayerInput(const float& dt)
{
	//check for keyboard key player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player.move(-1.f, 0.f, dt, this->isBuffed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player.move(1.f, 0.f, dt, this->isBuffed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player.move(0.f, -1.f, dt, this->isBuffed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player.move(0.f, 1.f, dt, this->isBuffed);
	}

	//For Testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		this->player.gainEXP(1);
		this->player.gainCoins(1);
		this->player.gainCrystals(1);
	}
}

inline void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		this->pauseMenu.playClickSound();

		if (!this->paused)
		{
			this->player.pauseSounds();
			this->pauseState();
		}
		else
		{
			this->unpausedState();
			this->skillMenuActive = false;
			this->itemsMenuActive = false;
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
		this->playerGUI.skillsMenUpdate(dt);
		this->skillsMenu.update(this->mousePosWindow, dt);
	}
	else if (this->paused && this->itemsMenuActive)
	{
		this->playerGUI.itemsMenuUpdate(dt);
		this->itemsMenu.update(this->mousePosWindow, dt);
	}
	else//Paused
	{
		this->pauseMenu.update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

inline void GameState::renderEnemies(sf::RenderTarget* target)
{
	for (auto& el : this->bosses)
	{
		if (!el.dead())
		{
			el.render(this->renderTexture, &this->core_shader);
		}
	}
	for (auto& el : this->meleEnemies)
	{
		if (!el.dead())
		{
			el.render(this->renderTexture, &this->core_shader);
		}
	}
	for (auto& el : this->mageEnemies)
	{
		if (!el.dead())
		{
			el.render(this->renderTexture, &this->core_shader);
		}
	}
	for (auto& el : this->destroyingEnemies)
	{
		if (!el.dead())
		{
			el.render(this->renderTexture, &this->core_shader);
		}
	}
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


	if (this->paused && !this->skillMenuActive && !this->itemsMenuActive) //Pause menu render
	{
		this->pauseMenu.render(this->renderTexture);
	}
	else if(this->paused && this->skillMenuActive && !this->itemsMenuActive) //Skills menu render
	{
		this->skillsMenu.render(this->renderTexture, this->mousePosWindow);
	}
	else if (this->paused && !this->skillMenuActive && this->itemsMenuActive) //Items menu render
	{
		this->itemsMenu.render(this->renderTexture, this->mousePosWindow);
	}

	//Render renderTexure
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
