#include <stdafx.h>
#include <States/GameState/GameState.h>

void GameState::updateVolumeText()
{
	this->volumeText.setString("Sounds volume: " + std::to_string(static_cast<int>(this->gameStateSoundBox.getVolume() * 100 / this->gameStateSoundBox.getMaxVolume())) + '%');
}

void GameState::updatePlayerInput(const float& dt)
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
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		this->player.gainEXP      (1);
		this->player.gainCoins    (1);
		this->player.gainCrystals (1);
	}*/
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime() && !this->gameOverMenuActive)
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

			//Gui render flag
			this->guiRenderFlag = false;
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
			this->guiRenderFlag = true;
		}
	}
	else if (this->gameOverMenuActive)
	{
		if (this->gameOverMenu.exitButtonIsPressed())
		{
			//Sound
			this->pauseMenu.playClickSound();

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

			//Quit
			this->endState();
		}
	}
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap.update(&this->player, this->viewGridPosition, dt);
}

void GameState::updateVolumeGui()
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
		if (this->gameStateSoundBox.getVolume() != this->gameStateSoundBox.getMaxVolume())
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

void GameState::updateView(const float& dt)
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

void GameState::updatePauseMenuButtons()
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

//Sound functions
void GameState::pauseSounds()
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

void GameState::resumeSounds()
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

void GameState::increaseVolume()
{
	this->gameStateSoundBox.increaseVolume();
	this->enemiesSoundBox.increaseVolume();
	this->guiSounBox.increaseVolume();
	this->player.increaseSoundsVolume();
	this->mapTrapsComponent.increaseSoundsVolume();
}

void GameState::decreaseVolume()
{
	if (this->gameStateSoundBox.getVolume() == 0)
	{
		this->enemiesSoundBox.setVolume(0);
		this->guiSounBox.setVolume(0);
		this->player.getSkillComponent()->setVolume(0);
		this->mapTrapsComponent.setSoundsVolume(0);
	}
	else
	{
		this->gameStateSoundBox.decreaseVolume();
		this->enemiesSoundBox.decreaseVolume();
		this->guiSounBox.decreaseVolume();
		this->player.decreaseSoundsVolume();
		this->mapTrapsComponent.decreaseSoundsVolume();
	}
}

//Render
void GameState::renderPauseMenuGui(sf::RenderTarget& target)
{
	//Volume text
	target.draw(this->volumeText);

	//Volume regulation buttons
	this->volumeButtons.first->render(target);
	this->volumeButtons.second->render(target);
}
