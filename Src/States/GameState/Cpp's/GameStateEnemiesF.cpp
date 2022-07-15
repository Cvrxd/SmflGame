#include <stdafx.h> 
#include <States/GameState/GameState.h>

void GameState::gameOverUpdate()
{
	if (this->player.dead())
	{
		this->gameOverMenuActive = true;

		this->pauseSounds();
		this->gameStateSoundBox.playGameOverMusic();
	}
}

void GameState::updateGameWave()
{
	//Wave count
	if ((++this->wavesCount) % BOSSWAVE == 0)
	{
		this->bossFight = true;

		//Generate boss enemies
		this->generateBossEnemies();

		//Update music
		this->gameStateSoundBox.pauseThemeMusic();
		this->gameStateSoundBox.playBossFightMusic();
	}
	else
	{
		this->bossFight = false;

		//Update music
		this->gameStateSoundBox.stopBossFightMusic();
		this->gameStateSoundBox.playThemeMusic();
	}

	//Enemies generation
	std::vector<std::thread> genataringThreads;
	genataringThreads.reserve(3);

	genataringThreads.push_back(std::thread(&GameState::generateMageEnemies, this));
	genataringThreads.push_back(std::thread(&GameState::generateDestroyingEnemies, this));
	genataringThreads.push_back(std::thread(&GameState::generateMeleEnemies, this));

	for (auto& el : genataringThreads)
	{
		if (el.joinable())
		{
			el.join();
		}
	}

	genataringThreads.clear();

	//Player potions
	this->player.addPotions(Potions::HEALTH);
	this->player.addPotions(Potions::MANA);
}

//Enemies update general
void GameState::updateEnemies(const float& dt)
{
	if (this->totalEnemies == this->player.getKillsCount())
	{
		this->updateGameWave();
	}

	//launch threads
	this->bossesEnemiesUpdateThread.launch();
	this->meleEnemiesUpdateThread.launch();
	this->magesUpdateThread.launch();
	this->destroyingEnemiesUpdateThread.launch();

	//Wait threads
	this->bossesEnemiesUpdateThread.wait();
	this->meleEnemiesUpdateThread.wait();
	this->magesUpdateThread.wait();
	this->destroyingEnemiesUpdateThread.wait();
}

//Enemies update separate
void GameState::updateDestroyingEnemis()
{
	for (auto& el : this->destroyingEnemies)
	{
		if (!el.dead())
		{
			el.update(*this->stateData->dt, this->mousPosView);
		}
	}
}

void GameState::updateMeleEnemies()
{
	for (auto& el : this->meleEnemies)
	{
		if (!el.dead())
		{
			el.update(*this->stateData->dt, this->mousPosView);
		}
	}
}

void GameState::updateBossEnemies()
{
	for (auto& el : this->bosses)
	{
		if (!el.dead())
		{
			el.update(*this->stateData->dt, this->mousPosView);
		}
	}
}

void GameState::updateMageEnemies()
{
	for (auto& el : this->mageEnemies)
	{
		if (!el.dead())
		{
			el.update(*this->stateData->dt, this->mousPosView);

			//Update collision
			this->tileMap.updateTilesCollision(&el, el.getGridPosition(static_cast<int>(this->gridSize)), *this->stateData->dt);
		}
	}
}

//Enemies generation functions
void GameState::generateMeleEnemies()
{
	//Enemy type and position
	MeleEnemyType rndEnemyType = MeleEnemyType::MIMIC;
	sf::Vector2f  enemyPosition;

	//Enemy lvl and amount
	int enemyLvl = 1;
	int enemiesAmount = EnemiesGenerationI<MeleEnemy>::generateAmount(this->wavesCount, this->diffcultyLvl, 2);

	this->totalEnemies += enemiesAmount;

	this->meleEnemiesGenerationI.clear();
	this->meleEnemiesGenerationI.reserve(enemiesAmount);

	for (int i = 0; i < enemiesAmount; ++i)
	{
		//Enemy type
		rndEnemyType = static_cast<MeleEnemyType>(std::rand() % (this->meleEnemiesTextures.size() - 1));

		//Enemy lvl
		enemyLvl = EnemiesGenerationI<MeleEnemy>::generateLvl(this->wavesCount, this->diffcultyLvl, 2);

		//Enemy position
		enemyPosition = EnemiesGenerationI<MeleEnemy>::generatePosition(this->tileMap.getMaxSizeF(), this->gridSize);

		this->meleEnemiesGenerationI.generate(rndEnemyType, enemyLvl, enemyPosition.x, enemyPosition.y, this->meleEnemiesTextures[rndEnemyType], &this->player, this->enemiesSoundBox);
	}
}

void GameState::generateMageEnemies()
{
	//Enemy type and position
	MageEnemyType rndEnemyType = MageEnemyType::NECROMANCER;
	sf::Vector2f  enemyPosition;

	//Enemy lvl and amount
	int enemyLvl = 1;
	int enemiesAmount = EnemiesGenerationI<MageEnemy>::generateAmount(this->wavesCount, this->diffcultyLvl, 1);

	this->totalEnemies += enemiesAmount;

	this->mageEnemiesGenerationI.clear();
	this->mageEnemiesGenerationI.reserve(enemiesAmount);

	for (int i = 0; i < enemiesAmount; ++i)
	{
		//Enemy type
		rndEnemyType = static_cast<MageEnemyType>(std::rand() % (this->mageEnemiesTextures.size() - 1));

		//Enemy lvl
		enemyLvl = EnemiesGenerationI<MageEnemy>::generateLvl(this->wavesCount, this->diffcultyLvl, 2);

		//Enemy position
		enemyPosition = EnemiesGenerationI<MageEnemy>::generatePosition(this->tileMap.getMaxSizeF(), this->gridSize);

		this->mageEnemiesGenerationI.generate(rndEnemyType, enemyLvl, enemyPosition.x, enemyPosition.y, this->mageEnemiesTextures[rndEnemyType], &this->player, this->enemiesSoundBox);
	}
}

void GameState::generateDestroyingEnemies()
{
	//Enemy type and position
	DestroyingEnemyType rndEnemyType = DestroyingEnemyType::FIRE_SKULL;
	sf::Vector2f  enemyPosition;

	//Enemy lvl and amount
	int enemyLvl = 1;
	int enemiesAmount = EnemiesGenerationI<DestroyingEnemy>::generateAmount(this->wavesCount, this->diffcultyLvl, 2);

	this->totalEnemies += enemiesAmount;

	this->destroyingEnemiesGenerationI.clear();
	this->destroyingEnemiesGenerationI.reserve(enemiesAmount);

	for (int i = 0; i < enemiesAmount; ++i)
	{
		//Enemy type
		rndEnemyType = static_cast<DestroyingEnemyType>(std::rand() % (this->destroyingEnemiestextures.size() - 1));

		//Enemy lvl
		enemyLvl = EnemiesGenerationI<MeleEnemy>::generateLvl(this->wavesCount, this->diffcultyLvl, 3);

		//Enemy position
		enemyPosition = EnemiesGenerationI<DestroyingEnemy>::generatePosition(this->tileMap.getMaxSizeF(), this->gridSize);

		this->destroyingEnemiesGenerationI.generate(rndEnemyType, enemyLvl, enemyPosition.x, enemyPosition.y, this->destroyingEnemiestextures[rndEnemyType], &this->player, this->enemiesSoundBox);
	}
}

void GameState::generateBossEnemies()
{
	//Enemy type and position
	BossType rndEnemyType = BossType::SAMURAI;
	sf::Vector2f  enemyPosition;

	//Enemy lvl and amount
	int enemyLvl = 1;
	int enemiesAmount = this->diffcultyLvl;

	this->totalEnemies += enemiesAmount;

	this->bossesGenerationI.clear();
	this->bossesGenerationI.reserve(enemiesAmount);

	for (int i = 0; i < enemiesAmount; ++i)
	{
		//Enemy type
		rndEnemyType = static_cast<BossType>(std::rand() % (this->destroyingEnemiestextures.size() - 1));

		//Enemy lvl
		enemyLvl = EnemiesGenerationI<BossEnemy>::generateLvl(this->wavesCount, this->diffcultyLvl, 4);

		//Enemy position
		enemyPosition = EnemiesGenerationI<BossEnemy>::generatePosition(this->tileMap.getMaxSizeF(), this->gridSize);

		this->bossesGenerationI.generate(rndEnemyType, enemyLvl, enemyPosition.x, enemyPosition.y, this->bossesEnemiesTextures[rndEnemyType], &this->player, this->enemiesSoundBox);
	}
}

//Render functions
void GameState::renderEnemies()
{
	this->renderBossEnemies();
	this->renderDestroyingEnemis();
	this->renderMageEnemies();
	this->renderMeleEnemies();
}

void GameState::renderDestroyingEnemis()
{
	for (auto& el : this->destroyingEnemies)
	{
		if (!el.dead())
		{
			el.render(this->renderTexture, &this->core_shader);
		}
	}
}

void GameState::renderMeleEnemies()
{
	for (auto& el : this->meleEnemies)
	{
		if (!el.dead())
		{
			el.render(this->renderTexture, &this->core_shader);
		}
	}
}

void GameState::renderBossEnemies()
{
	for (auto& el : this->bosses)
	{
		if (!el.dead())
		{
			el.render(this->renderTexture, &this->core_shader);
		}
	}
}

void GameState::renderMageEnemies()
{
	for (auto& el : this->mageEnemies)
	{
		if (!el.dead())
		{
			el.render(this->renderTexture, &this->core_shader);
		}
	}
}
