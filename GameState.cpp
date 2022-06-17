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

	this->renderSprite.setTextureRect(sf::IntRect(0, 0, 
		this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height));
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
	//Player
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
	this->textures["ENEMY_WIZZARD"].loadFromFile("Textures/enemies/mages/wizzard.png");
	this->textures["ENEMY_NECROMANCER"].loadFromFile("Textures/enemies/mages/necromancer.png");

	//Destroying enemies
	this->textures["ENEMY_FIRE_SKULL"].loadFromFile("Textures/enemies/destroying/fire-skull.png");
	this->textures["ENEMY_FIRE_WORM"].loadFromFile("Textures/enemies/destroying/fire_worm.png");
	this->textures["ENEMY_DRAGON"].loadFromFile("Textures/enemies/destroying/dragon.png");
}

inline void GameState::initPauseMenu()
{
	//Pause menu buttons
	this->pauseMenu.addButton("CONTINUE", 350.f, -20.f,"Continue");
	this->pauseMenu.addButton("SKILLS", 500.f, 20.f, "Skills");
	this->pauseMenu.addButton("ITEMS", 650.f, 20.f, "items");
	this->pauseMenu.addButton("QUIT", 800.f, 40.f,"Quit");

	//Volume text
	this->volumeText.setFont          (this->font);
	this->volumeText.setCharacterSize (40);
	this->volumeText.setString        ("Music volume: " + std::to_string(static_cast<int>(this->gameStateSoundBox.getVolume() * 100 / this->gameStateSoundBox.getVolumeMax())) + '%');
	this->volumeText.setFillColor     (sf::Color(255, 255, 255, 200));
	this->volumeText.setPosition      (static_cast<float>(this->window->getSize().x) - 400.f, 100.f);

	//Volume buttons
	this->volumeButtons.first = std::make_unique<GUI::Button>(this->volumeText.getPosition().x + 240.f, this->volumeText.getPosition().y + 20.f, 
		70.f, 60.f,
		&this->font, "-", 65,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0),      sf::Color(150, 150, 150, 0),   sf::Color(20, 20, 20, 0)
		);

	this->volumeButtons.second = std::make_unique<GUI::Button>(
		this->volumeButtons.first->getPosition().x + 60.f, this->volumeButtons.first->getPosition().y, 
		70.f, 60.f,
		&this->font, "+", 65,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0),      sf::Color(150, 150, 150, 0),   sf::Color(20, 20, 20, 0)
		);
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
	this->bosses.emplace_back(BossType::FIRE_DEMON, 5, 100, 900, this->textures["ENEMY_FIRE_DEMON"], &this->player, this->enemiesSoundBox);
	//this->bosses.emplace_back(BossType::NIGHTBORN, 5, 100, 900, this->textures["ENEMY_NIGHT_BORN"], &this->player, this->enemiesSoundBox);
	//this->bosses.emplace_back(BossType::SAMURAI, 5, 100, 900, this->textures["ENEMY_SAMURAI"], &this->player, this->enemiesSoundBox);

	this->meleEnemies.reserve(3);
	//this->meleEnemies.emplace_back(MeleEnemyType::KNIGHT1, 5, 700, 700, this->textures["ENEMY_KNIGHT1"], &this->player, this->enemiesSoundBox);
	//this->meleEnemies.emplace_back(MeleEnemyType::BRINGER_OF_DEATH, 5, 700, 700, this->textures["ENEMY_BRINGER_OF_DEATH"], &this->player, this->enemiesSoundBox);
	//this->meleEnemies.emplace_back(MeleEnemyType::BRINGER_OF_DEATH, 5, 700, 700, this->textures["ENEMY_BRINGER_OF_DEATH"], &this->player, this->enemiesSoundBox);

	this->mageEnemies.reserve(2);
	//this->mageEnemies.emplace_back(MageEnemyType::DARK_MAGE, 1, 400, 400, this->textures["ENEMY_DARK_MAGE"], &this->player, this->enemiesSoundBox);
	//this->mageEnemies.emplace_back(MageEnemyType::NECROMANCER, 1, 500, 400, this->textures["ENEMY_NECROMANCER"], &this->player, this->enemiesSoundBox);
	
	this->destroyingEnemies.reserve(2);
	//this->destroyingEnemies.emplace_back(DestroyingEnemyType::DRAGON, 1, 0, 0, this->textures["ENEMY_DRAGON"], &this->player,this->enemiesSoundBox);
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
	this->gameStateSoundBox.playThemeMusic();
}

//Update functions
inline void GameState::updateVolumeText()
{
	this->volumeText.setString("Music volume: "+ std::to_string(static_cast<int>(this->gameStateSoundBox.getVolume() * 100 / this->gameStateSoundBox.getVolumeMax())) + '%');
}

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
			//Pausing sounds
			this->pauseSounds();

			//Pausing state
			this->pauseState();

			//Playing pause menu music
			this->gameStateSoundBox.playPauseMenuMusic();
		}
		else
		{
			//Unpausing sounds
			this->resumeSounds();

			//Stoping gui and pause menu sounds
			this->gameStateSoundBox.stopPauseMenuMusic();
			this->guiSounBox.stopSounds();

			//Unpausing state
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

inline void GameState::updateVolumeGui()
{
	this->volumeButtons.first->update(this->mousePosWindow);
	this->volumeButtons.second->update(this->mousePosWindow);

	//Decreasing volume button
	if (this->volumeButtons.first->isPressed() && this->getKeyTime())
	{
		//Sound
		this->guiSounBox.sounds["CLICK"].second.play();

		//Decreasing volume
		this->decreaseVolume();

		//Updating volume value text
		this->updateVolumeText();
	}

	//Increasing volume button
	if (this->volumeButtons.second->isPressed() && this->getKeyTime())
	{
		if (this->gameStateSoundBox.getVolume() != this->gameStateSoundBox.getVolumeMax())
		{
			//Sound
			this->guiSounBox.sounds["CLICK"].second.play();

			//Increasing volume
			this->increaseVolume();

			//Updating volume value text
			this->updateVolumeText();
		}
	}
}

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

		//Resuming sounds
		this->resumeSounds();

		//Stoping gui and pause menu sounds
		this->gameStateSoundBox.stopPauseMenuMusic();

		this->guiSounBox.stopSounds();

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

//Enemies update general
inline void GameState::updateEnemies(const float& dt)
{
	this->updateBossEnemies      (dt);
	this->updateDestroyingEnemis (dt);
	this->updateMageEnemies      (dt);
	this->updateMeleEnemies      (dt);
}

//Enemies update separate
inline void GameState::updateDestroyingEnemis(const float& dt)
{
	for (auto& el : this->destroyingEnemies)
	{
		if (!el.dead())
		{
			el.update(dt, this->mousPosView);
		}
	}
}

inline void GameState::updateMeleEnemies(const float& dt)
{
	for (auto& el : this->meleEnemies)
	{
		if (!el.dead())
		{
			el.update(dt, this->mousPosView);
		}
	}
}

inline void GameState::updateBossEnemies(const float& dt)
{
	for (auto& el : this->bosses)
	{
		if (!el.dead())
		{
			el.update(dt, this->mousPosView);
		}
	}
}

inline void GameState::updateMageEnemies(const float& dt)
{
	for (auto& el : this->mageEnemies)
	{
		if (!el.dead())
		{
			el.update(dt, this->mousPosView);

			//Update collision
			this->tileMap.updateTilesCollision(&el, el.getGridPosition(static_cast<int>(this->gridSize)), dt);
		}
	}
}

//Render functions
inline void GameState::renderEnemies(sf::RenderTarget& target)
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

inline void GameState::renderPauseMenuGui(sf::RenderTarget& target)
{
	//Volume text
	target.draw(this->volumeText);

	//Volume regulation buttons
	this->volumeButtons.first->render(target);
	this->volumeButtons.second->render(target);
}

//Sound functions
inline void GameState::pauseSounds()
{
	//Pausing player sounds
	this->player.pauseSounds();

	//Pausing music
	if (!this->bossFight)
	{
		this->gameStateSoundBox.pauseThemeMusic();
	}
	else
	{
		this->gameStateSoundBox.pauseBossFightMusic();
	}

	//Pausing enemies sounds
	for (auto& el : this->destroyingEnemies)
	{
		if (!el.dead())
		{
			el.pauseSounds();
		}
	}
	for (auto& el : this->mageEnemies)
	{
		if (!el.dead())
		{
			el.pauseSounds();
		}
	}
	for (auto& el : this->bosses)
	{
		if (!el.dead())
		{
			el.pauseSounds();
		}
	}
	for (auto& el : this->meleEnemies)
	{
		if (!el.dead())
		{
			el.pauseSounds();
		}
	}
}

inline void GameState::resumeSounds()
{
	//Resuming player sounds
	this->player.playSounds();

	//Resuming music
	if (!this->bossFight)
	{
		this->gameStateSoundBox.playThemeMusic();
	}
	else
	{
		this->gameStateSoundBox.playBossFightMusic();
	}

	//Resuming enemies sounds
	for (auto& el : this->destroyingEnemies)
	{
		if (!el.dead())
		{
			el.resumeSounds();
		}
	}
	for (auto& el : this->mageEnemies)
	{
		if (!el.dead())
		{
			el.resumeSounds();
		}
	}
	for (auto& el : this->bosses)
	{
		if (!el.dead())
		{
			el.resumeSounds();
		}
	}
	for (auto& el : this->meleEnemies)
	{
		if (!el.dead())
		{
			el.resumeSounds();
		}
	}
}

inline void GameState::increaseVolume()
{
	this->gameStateSoundBox.increaseVolume ();
	this->enemiesSoundBox.increaseVolume   ();
	this->guiSounBox.increaseVolume        ();
	this->player.increaseSoundsVolume      ();
}

inline void GameState::decreaseVolume()
{
	this->gameStateSoundBox.decreaseVolume ();
	this->enemiesSoundBox.decreaseVolume   ();
	this->guiSounBox.decreaseVolume        ();
	this->player.decreaseSoundsVolume      ();
}

//Constructor
GameState::GameState(StateData* state_data, const unsigned int& difficultyLvl)
	: 
	State(state_data), 

	diffcultyLvl       (difficultyLvl),
	skillMenuActive    (false),
	popUpTextComponent (state_data->font),

	pauseMenu   (*this->window, this->stateData->font),                                //Pause menu 
	player      (500, 500, this->textures["PLAYER_SHEET"], this->font, this->isBuffed), //Player
	playerGUI   (this->player, this->font),                                            //Player GUI
	tileMap     ("map/game_map.txt"),                                                  //Tile Map

	skillsMenu  (this->player, this->playerGUI,this->font, this->guiSounBox, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)), // Skills menu
	itemsMenu   (this->player, this->playerGUI, this->font, this->guiSounBox, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)) // items menu                                                //Tile map
{
	//State type
	this->type = STATE_TYPE::GAME_STATE;

	//Init functions
	this->initRenderTextures ();
	this->initView           ();
	this->initFonts          ();
	this->initKeybinds       ();
	this->initTextures       ();
	this->initPauseMenu      ();
	this->initSounds         ();
	this->initEnemies        ();
	this->initShaders        ();
	this->initPlayerGUI      ();
}

GameState::~GameState()
{
}

//Public functions
void GameState::updateTopState()
{
}

void GameState::update(const float& dt)
{
	this->updateMousePosition (&this->view);
	this->updateKeyTime       (dt);
	this->updateInput         (dt);
	
	if (!this->paused) //Update game
	{
		this->updateView        (dt);
		this->updateEnemies     (dt);
		this->updatePlayerInput (dt);
		this->updateTileMap     (dt);
		this->player.update     (dt, this->mousPosView);

		//Player gui update
		this->playerGUI.update(dt);
	} 
	else if (this->paused && this->skillMenuActive) //Update skills menu
	{
		this->playerGUI.skillsMenUpdate(dt);
		this->skillsMenu.update(this->mousePosWindow, dt);
	}
	else if (this->paused && this->itemsMenuActive) //Update items menu
	{
		this->playerGUI.itemsMenuUpdate(dt);
		this->itemsMenu.update(this->mousePosWindow, dt);
	}
	else                                            //Update pause menu
	{
		this->pauseMenu.update(this->mousePosWindow);

		this->updatePauseMenuButtons();
		this->updateVolumeGui();
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

	this->tileMap.renderGameState  (this->renderTexture, this->player.getCenter(), &this->core_shader);  //Render tile map
	this->renderEnemies            (*target);                                                            //Render all enemies
	this->player.render            (this->renderTexture, &this->core_shader);                            //Render player
	this->tileMap.renderAbove      (this->renderTexture, this->player.getCenter(), &this->core_shader);  //Render tiles above entities
	this->renderTexture.setView    (this->renderTexture.getDefaultView());                               //Seting view
	this->playerGUI.render         (this->renderTexture);                                                //Render player GUI

	if (this->paused && !this->skillMenuActive && !this->itemsMenuActive) //Pause menu render
	{
		this->pauseMenu.render   (this->renderTexture);
		this->renderPauseMenuGui (this->renderTexture);
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

	//Final rendering using render sprite
	target->draw(this->renderSprite);
}
