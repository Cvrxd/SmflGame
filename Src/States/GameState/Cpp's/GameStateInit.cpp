#include <stdafx.h>
#include <States/GameState/GameState.h>

//Initialisation
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

	this->renderSprite.setTextureRect(sf::IntRect(0, 0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height));
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
		static_cast<float>(this->stateData->gfxSettings->resolution.height)));

	this->view.setCenter(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width / 2.f,
		this->stateData->gfxSettings->resolution.height / 2.f));

}

void GameState::initFonts()
{
	this->font.loadFromFile("Fonts/Greybeard.ttf");
}

void GameState::initTextures()
{
	//Player
	this->textures["PLAYER_SHEET"].loadFromFile("Textures/characters/player/player_sheet.png");

	//Bosses
	this->bossesEnemiesTextures[BossType::SAMURAI].loadFromFile("Textures/enemies/boses/samurai.png");
	this->bossesEnemiesTextures[BossType::NIGHTBORN].loadFromFile("Textures/enemies/boses/NightBorne.png");
	this->bossesEnemiesTextures[BossType::FIRE_DEMON].loadFromFile("Textures/enemies/boses/fire_demon.png");

	//Mele enemies
	this->meleEnemiesTextures[MeleEnemyType::BRINGER_OF_DEATH].loadFromFile("Textures/enemies/mele/bringer_of_death.png");
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

void GameState::initPauseMenu()
{
	//Pause menu buttons
	this->pauseMenu.addButton("CONTINUE", 300.f, -20.f, "Continue");
	this->pauseMenu.addButton("SKILLS", 450.f, 20.f, "Skills");
	this->pauseMenu.addButton("ITEMS", 600.f, 20.f, "items");
	this->pauseMenu.addButton("QUIT", 750.f, 40.f, "Quit");

	//Volume text
	this->volumeText.setFont(this->font);
	this->volumeText.setCharacterSize(40);
	this->volumeText.setString("Sounds volume: " + std::to_string(static_cast<int>(this->gameStateSoundBox.getVolume() * 100 / this->gameStateSoundBox.getVolumeMax())) + '%');
	this->volumeText.setFillColor(sf::Color(255, 255, 255, 200));
	this->volumeText.setPosition(static_cast<float>(this->window->getSize().x) - 400.f, 100.f);

	//Volume buttons
	this->volumeButtons.first = std::make_unique<GUI::Button>(this->volumeText.getPosition().x + 240.f, this->volumeText.getPosition().y + 20.f,
		70.f, 60.f, &this->font, "-", 65);

	this->volumeButtons.second = std::make_unique<GUI::Button>(
		this->volumeButtons.first->getPosition().x + 60.f, this->volumeButtons.first->getPosition().y,
		70.f, 60.f, &this->font, "+", 65);
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "Shader error";
	}
}

void GameState::initPlayers()
{
}

void GameState::initPlayerGUI()
{
	this->player.setPlayerGUI(this->playerGUI);
}

void GameState::initTileMap()
{
	this->tileMap.loadFromFile("map/game_map.txt");
}

void GameState::initSounds()
{
	this->gameStateSoundBox.playThemeMusic();
}

void GameState::createTraps()
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
