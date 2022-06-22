#include "stdafx.h" 
#include "GameState.h"

#define GENERATR_ENEMY_POSITION enemyPosition.x = static_cast<float>(std::rand() % (static_cast<int>(this->tileMap.getMaxSizeF().x - this->gridSize)) + this->gridSize);\
								enemyPosition.y = static_cast<float>(std::rand() % (static_cast<int>(this->tileMap.getMaxSizeF().y - this->gridSize)) + this->gridSize)


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

	this->view.setCenter(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width / 2.f, 
		this->stateData->gfxSettings->resolution.height / 2.f));

}

inline void GameState::initFonts()
{
	this->font.loadFromFile("Fonts/Greybeard.ttf");
}

inline void GameState::initTextures()
{
	//Player
	this->textures["PLAYER_SHEET"].loadFromFile("Textures/characters/player/test_sheet.png");

	//Bosses
	this->bossesEnemiesTextures[BossType::SAMURAI].loadFromFile("Textures/enemies/boses/samurai.png");
	this->bossesEnemiesTextures[BossType::NIGHTBORN].loadFromFile("Textures/enemies/boses/NightBorne.png");
	this->bossesEnemiesTextures[BossType::FIRE_DEMON].loadFromFile("Textures/enemies/boses/fire_demon.png");

	//Mele enemies
	this->meleEnemiesTextures[MeleEnemyType::BRINGER_OF_DEATH].loadFromFile("Textures/enemies/mele/bringer_of_death.png");
	this->meleEnemiesTextures[MeleEnemyType::NOMAND].loadFromFile("Textures/enemies/mele/nomand.png");
	this->meleEnemiesTextures[MeleEnemyType::MIMIC].loadFromFile("Textures/enemies/mele/mimic.png");
	this->meleEnemiesTextures[MeleEnemyType::KNIGHT1].loadFromFile("Textures/enemies/mele/knight1.png");
	this->meleEnemiesTextures[MeleEnemyType::HUNTRESS].loadFromFile("Textures/enemies/mele/huntress.png");
	this->meleEnemiesTextures[MeleEnemyType::MARTIAL_HERO1].loadFromFile("Textures/enemies/mele/martial_hero1.png");
	this->meleEnemiesTextures[MeleEnemyType::MARTIAL_HERO2].loadFromFile("Textures/enemies/mele/martial_hero2.png");

	//Mages
	this->mageEnemiesTextures[MageEnemyType::DARK_MAGE].loadFromFile("Textures/enemies/mages/dark_mage.png");
	this->mageEnemiesTextures[MageEnemyType::FIRE_MAGE].loadFromFile("Textures/enemies/mages/fire_mage.png");
	this->mageEnemiesTextures[MageEnemyType::WIZZARD].loadFromFile("Textures/enemies/mages/wizzard.png");
	this->mageEnemiesTextures[MageEnemyType::NECROMANCER].loadFromFile("Textures/enemies/mages/necromancer.png");

	//Destroying enemies
	this->destroyingEnemiestextures[DestroyingEnemyType::FIRE_SKULL].loadFromFile("Textures/enemies/destroying/fire-skull.png");
	this->destroyingEnemiestextures[DestroyingEnemyType::FIRE_WORM].loadFromFile("Textures/enemies/destroying/fire_worm.png");
	this->destroyingEnemiestextures[DestroyingEnemyType::DRAGON].loadFromFile("Textures/enemies/destroying/dragon.png");
}

inline void GameState::initPauseMenu()
{
	//Pause menu buttons
	this->pauseMenu.addButton("CONTINUE", 300.f, -20.f,"Continue");
	this->pauseMenu.addButton("SKILLS", 450.f, 20.f, "Skills");
	this->pauseMenu.addButton("ITEMS", 600.f, 20.f, "items");
	this->pauseMenu.addButton("QUIT", 750.f, 40.f,"Quit");

	//Volume text
	this->volumeText.setFont          (this->font);
	this->volumeText.setCharacterSize (40);
	this->volumeText.setString        ("Sounds volume: " + std::to_string(static_cast<int>(this->gameStateSoundBox.getVolume() * 100 / this->gameStateSoundBox.getVolumeMax())) + '%');
	this->volumeText.setFillColor     (sf::Color(255, 255, 255, 200));
	this->volumeText.setPosition      (static_cast<float>(this->window->getSize().x) - 400.f, 100.f);

	//Volume buttons
	this->volumeButtons.first = std::make_unique<GUI::Button>(this->volumeText.getPosition().x + 240.f, this->volumeText.getPosition().y + 20.f, 
		70.f, 60.f, &this->font, "-", 65);

	this->volumeButtons.second = std::make_unique<GUI::Button>(
		this->volumeButtons.first->getPosition().x + 60.f, this->volumeButtons.first->getPosition().y, 
		70.f, 60.f, &this->font, "+", 65);
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
	//this->bosses.emplace_back(BossType::FIRE_DEMON, 5, 100, 900, this->textures["ENEMY_FIRE_DEMON"], &this->player, this->enemiesSoundBox);
	//this->bosses.emplace_back(BossType::NIGHTBORN, 5, 100, 900, this->textures["ENEMY_NIGHT_BORN"], &this->player, this->enemiesSoundBox);
	//this->bosses.emplace_back(BossType::SAMURAI, 5, 100, 900, this->textures["ENEMY_SAMURAI"], &this->player, this->enemiesSoundBox);

	//this->meleEnemies.emplace_back(MeleEnemyType::KNIGHT1, 5, 700, 700, this->textures["ENEMY_KNIGHT1"], &this->player, this->enemiesSoundBox);
	//this->meleEnemies.emplace_back(MeleEnemyType::BRINGER_OF_DEATH, 5, 700, 700, this->textures["ENEMY_BRINGER_OF_DEATH"], &this->player, this->enemiesSoundBox);
	//this->meleEnemies.emplace_back(MeleEnemyType::BRINGER_OF_DEATH, 5, 700, 700, this->textures["ENEMY_BRINGER_OF_DEATH"], &this->player, this->enemiesSoundBox);

	//this->mageEnemies.emplace_back(MageEnemyType::DARK_MAGE, 1, 400, 400, this->textures["ENEMY_DARK_MAGE"], &this->player, this->enemiesSoundBox);
	//this->mageEnemies.emplace_back(MageEnemyType::NECROMANCER, 1, 500, 400, this->textures["ENEMY_NECROMANCER"], &this->player, this->enemiesSoundBox);

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

inline void GameState::createTraps()
{
	this->mapTrapsComponent.addTrap(650.f, 700.f, TrapType::FIRE_TRAP);
	this->mapTrapsComponent.addTrap(1450.f, 520.f, TrapType::SPIKE_TRAP);
	this->mapTrapsComponent.addTrap(1530.f, 1000.f, TrapType::FIRE_TRAP);
	this->mapTrapsComponent.addTrap(650.f, 1360.f, TrapType::FIRE_TRAP);
	this->mapTrapsComponent.addTrap(950.f, 1770.f, TrapType::SPIKE_TRAP);
	this->mapTrapsComponent.addTrap(500.f, 2350.f, TrapType::SPIKE_TRAP);
	this->mapTrapsComponent.addTrap(1360.f, 2680.f, TrapType::FIRE_TRAP);
	this->mapTrapsComponent.addTrap(1860.f, 1230.f, TrapType::SPIKE_TRAP);
	this->mapTrapsComponent.addTrap(1300.f, 1670.f, TrapType::FIRE_TRAP);
	this->mapTrapsComponent.addTrap(2380.f, 1700.f, TrapType::SPIKE_TRAP);
	this->mapTrapsComponent.addTrap(2020.f, 2900.f, TrapType::FIRE_TRAP);
	this->mapTrapsComponent.addTrap(2396.f, 2650.f, TrapType::SPIKE_TRAP);
	this->mapTrapsComponent.addTrap(2810.f, 1840.f, TrapType::FIRE_TRAP);
	this->mapTrapsComponent.addTrap(2700.f, 1425.f, TrapType::SPIKE_TRAP);
	this->mapTrapsComponent.addTrap(2690, 620.f, TrapType::FIRE_TRAP);
}

//Update functions
inline void GameState::updateGameWave()
{
	//Wave count
	if ((++this->wavesCount) % 5 == 0)
	{
		this->bossFight = true;

		//Generate boss enemies
		this->generateBossEnemies();
	}

	//Enemies generation
	this->generateDestroyingEnemies ();
	this->generateMageEnemies       ();
	this->generateMeleEnemies       ();
}

inline void GameState::updateVolumeText()
{
	this->volumeText.setString("Sounds volume: "+ std::to_string(static_cast<int>(this->gameStateSoundBox.getVolume() * 100 / this->gameStateSoundBox.getVolumeMax())) + '%');
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

	//World view
	if (this->tileMap.getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < this->gridSize)
		{
			this->view.setCenter(this->gridSize + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap.getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap.getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap.getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < this->gridSize)
		{
			this->view.setCenter(this->view.getCenter().x, this->gridSize + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap.getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap.getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x / static_cast<int>(this->stateData->gridSize));
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y / static_cast<int>(this->stateData->gridSize));
}

inline void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu.isButtonPressed("QUIT"))
	{
		//Update record info
		if (this->player.getKillsCount() > this->recordInfo.kills)         //Enemies kills count
		{
			this->recordInfo.kills = this->player.getKillsCount();
		}
		if (this->player.getBossKillsCount() > this->recordInfo.bossKills) //Boss kills count
		{
			this->recordInfo.bossKills = this->player.getBossKillsCount();
		}
		if (this->wavesCount > this->recordInfo.wavesCount)                //Total waves survived
		{
			this->recordInfo.wavesCount = this->wavesCount;
		}
		if (this->player.getTotalCoins() > this->recordInfo.coins)         //Total coins earned
		{
			this->recordInfo.coins = this->player.getTotalCoins();
		}
		if (this->player.getTotalCrystals() > this->recordInfo.crystals)   //Total crystals earned
		{
			this->recordInfo.crystals = this->player.getTotalCrystals();
		}

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

//Enemies generation functions
inline void GameState::generateMeleEnemies()
{
	//Enemy type and position
	MeleEnemyType rndEnemyType = MeleEnemyType::MIMIC;
	sf::Vector2f  enemyPosition;

	//Enemy lvl and amount
	int enemyLvl = 1;
	int enemiesAmount = this->diffcultyLvl * 3 + this->wavesCount / 5;

	this->meleEnemiesGenerationI.clear();
	this->meleEnemiesGenerationI.reserve(enemiesAmount);

	for (int i = 0; i < enemiesAmount; ++i)
	{
		//Enemy type
		rndEnemyType = static_cast<MeleEnemyType>(std::rand() % (this->meleEnemiesTextures.size() - 1));

		//Enemy lvl
		enemyLvl = this->player.getLvl() + this->diffcultyLvl + (this->diffcultyLvl * std::rand() % 3);

		//Enemy position
		GENERATR_ENEMY_POSITION;

		this->meleEnemiesGenerationI.generate(rndEnemyType, enemyLvl, enemyPosition.x, enemyPosition.y, this->meleEnemiesTextures[rndEnemyType], &this->player, this->enemiesSoundBox);
	}
}

inline void GameState::generateMageEnemies()
{
	//Enemy type and position
	MageEnemyType rndEnemyType = MageEnemyType::DARK_MAGE;
	sf::Vector2f  enemyPosition;

	//Enemy lvl and amount
	int enemyLvl = 1;
	int enemiesAmount = this->diffcultyLvl * 2 + this->wavesCount / 5;

	this->mageEnemiesGenerationI.clear();
	this->mageEnemiesGenerationI.reserve(enemiesAmount);

	for (int i = 0; i < enemiesAmount; ++i)
	{
		//Enemy type
		rndEnemyType = static_cast<MageEnemyType>(std::rand() % (this->mageEnemiesTextures.size() - 1));

		//Enemy lvl
		enemyLvl = this->player.getLvl() + this->diffcultyLvl + (this->diffcultyLvl * std::rand() % 3);

		//Enemy position
		GENERATR_ENEMY_POSITION;

		this->mageEnemiesGenerationI.generate(rndEnemyType, enemyLvl, enemyPosition.x, enemyPosition.y, this->mageEnemiesTextures[rndEnemyType], &this->player, this->enemiesSoundBox);
	}
}

inline void GameState::generateDestroyingEnemies()
{
	//Enemy type and position
	DestroyingEnemyType rndEnemyType = DestroyingEnemyType::FIRE_SKULL;
	sf::Vector2f  enemyPosition;

	//Enemy lvl and amount
	int enemyLvl = 1;
	int enemiesAmount = this->diffcultyLvl * 2 + this->wavesCount / 5;

	this->destroyingEnemiesGenerationI.clear();
	this->destroyingEnemiesGenerationI.reserve(enemiesAmount);

	for (int i = 0; i < enemiesAmount; ++i)
	{
		//Enemy type
		rndEnemyType = static_cast<DestroyingEnemyType>(std::rand() % (this->destroyingEnemiestextures.size() - 1));

		//Enemy lvl
		enemyLvl = this->player.getLvl() + this->diffcultyLvl + (this->diffcultyLvl * std::rand() % 3);

		//Enemy position
		GENERATR_ENEMY_POSITION;

		this->destroyingEnemiesGenerationI.generate(rndEnemyType, enemyLvl, enemyPosition.x, enemyPosition.y, this->destroyingEnemiestextures[rndEnemyType], &this->player, this->enemiesSoundBox);
	}
}

inline void GameState::generateBossEnemies()
{
	//Enemy type and position
	BossType rndEnemyType = BossType::SAMURAI;
	sf::Vector2f  enemyPosition;

	//Enemy lvl and amount
	int enemyLvl      = 1;
	int enemiesAmount = this->diffcultyLvl;

	this->bossesGenerationI.clear();
	this->bossesGenerationI.reserve(enemiesAmount);

	for (int i = 0; i < enemiesAmount; ++i)
	{
		//Enemy type
		rndEnemyType = static_cast<BossType>(std::rand() % (this->destroyingEnemiestextures.size() - 1));

		//Enemy lvl
		enemyLvl = 5 + (this->diffcultyLvl * (std::rand() % 5));

		//Enemy position
		GENERATR_ENEMY_POSITION;

		this->bossesGenerationI.generate(rndEnemyType, enemyLvl, enemyPosition.x, enemyPosition.y, this->bossesEnemiesTextures[rndEnemyType], &this->player, this->enemiesSoundBox);
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
	//Pausing traps sounds
	this->mapTrapsComponent.pauseSounds();

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
	//Resuming traps sound
	this->mapTrapsComponent.playSounds();

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
	this->gameStateSoundBox. increaseVolume        ();
	this->enemiesSoundBox.   increaseVolume        ();
	this->guiSounBox.        increaseVolume        ();
	this->player.            increaseSoundsVolume  ();
	this->mapTrapsComponent. increaseSoundsVolume  ();
}

inline void GameState::decreaseVolume()
{
	if (this->gameStateSoundBox.getVolume() == 0)
	{
		this->enemiesSoundBox.setVolume                   (0);
		this->guiSounBox.setVolume                        (0);
		this->player.getSkillComponent()->setSoundsVolume (0);
		this->mapTrapsComponent.setSoundsVolume           (0);
	}
	else
	{
		this->gameStateSoundBox.decreaseVolume       ();
		this->enemiesSoundBox.decreaseVolume         ();
		this->guiSounBox.decreaseVolume              ();
		this->player.decreaseSoundsVolume            ();
		this->mapTrapsComponent.decreaseSoundsVolume ();
	}
}

//Constructor
GameState::GameState(StateData* state_data, RecordInfo& info, const unsigned int& difficultyLvl)
	: 
	State(state_data), 

	recordInfo         (info),
	diffcultyLvl       (difficultyLvl),
	skillMenuActive    (false),

	bossesGenerationI            (this->bosses),              //Bosses generation interface
	meleEnemiesGenerationI       (this->meleEnemies),         //Mele enemies generation interface
	mageEnemiesGenerationI       (this->mageEnemies),         //Mage enemies generation interface
	destroyingEnemiesGenerationI (this->destroyingEnemies),   //Destroying enemies generation interface

	pauseMenu          (*this->window, this->stateData->font),                                  //Pause menu 
	player             (500, 500, this->textures["PLAYER_SHEET"], this->font, this->isBuffed),  //Player
	playerGUI          (this->player, this->font, *state_data->window),                         //Player GUI
	tileMap            ("map/game_map.txt"),                                                    //Tile Map
	mapTrapsComponent  (this->player, this->diffcultyLvl, this->trapsCount),

	skillsMenu         (this->player, this->playerGUI,this->font, this->guiSounBox, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)), // Skills menu
	itemsMenu          (this->player, this->playerGUI, this->font, this->guiSounBox, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)) // items menu                                                //Tile map
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
	this->createTraps        ();

	//Test
	this->updateGameWave();
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
		this->updateView               (dt);
		this->updateEnemies            (dt);
		this->updatePlayerInput        (dt);
		this->updateTileMap            (dt);
		this->player.update            (dt, this->mousPosView);
		this->mapTrapsComponent.update (dt);

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
	//Set render texture
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);

	//Rendering
	this->tileMap.renderGameState  (this->renderTexture, this->player.getCenter(), &this->core_shader);  //Render tile map
	this->renderEnemies            (*target);                                                            //Render all enemies
	this->mapTrapsComponent.render (this->renderTexture);                                                //Render traps
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

	//Final rendering using render sprite
	target->draw(this->renderSprite);
}
