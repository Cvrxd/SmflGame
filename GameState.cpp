#include "stdafx.h" 
#include "GameState.h"

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

	gameOverMenu       (*state_data->window, state_data->font),                                               //Game over menu
	pauseMenu          (*state_data->window, state_data->font),                                               //Pause menu 
	player             (500, 500, this->textures["PLAYER_SHEET"], this->font, this->isBuffed),                //Player
	playerGUI          (this->player, this->font, *state_data->window, this->wavesCount, this->diffcultyLvl), //Player GUI
	tileMap            ("map/game_map.txt"),                                                                  //Tile Map
	mapTrapsComponent  (this->player, this->diffcultyLvl, this->trapsCount),

	skillsMenu         (this->player, this->playerGUI,this->font, this->guiSounBox, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)),  // Skills menu
	itemsMenu          (this->player, this->playerGUI, this->font, this->guiSounBox, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)), // items menu

	magesUpdateThread             (&GameState::updateMageEnemies, this),        //Thread for mages update
	meleEnemiesUpdateThread       (&GameState::updateMeleEnemies, this),        //Thread for mele enemies update
	bossesEnemiesUpdateThread     (&GameState::updateBossEnemies, this),        //Thread for bosses update
	destroyingEnemiesUpdateThread (&GameState::updateDestroyingEnemis, this)    //Thread for destroying enemies update
{
	//State type
	this->type = STATE_TYPE::GAME_STATE;

	//Init functions
	std::thread initTexturesThread(&GameState::initTextures, this); //Thread for loading textures

	this->initRenderTextures ();
	this->initView           ();
	this->initFonts          ();
	this->initKeybinds       ();
	this->initPauseMenu      ();
	this->initSounds         ();
	this->initShaders        ();
	this->initPlayerGUI      ();
	this->createTraps        ();

	initTexturesThread.join();

	//Start game
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

	if (!this->paused && !this->gameOverMenuActive) //Update game
	{
		this->gameOverUpdate           ();
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
		this->playerGUI.itemsMenuUpdate (dt);
		this->itemsMenu.update          (this->mousePosWindow, dt);
	}
	else if(this->paused && !this->itemsMenuActive && !this->skillMenuActive)//Update pause menu
	{
		this->pauseMenu.update(this->mousePosWindow);

		this->updatePauseMenuButtons ();
		this->updateVolumeGui        ();
	}
	else if (this->gameOverMenuActive) //Update game over menu
	{
		this->gameOverMenu.update(dt, this->mousePosWindow);
	}
	
}

void GameState::render(sf::RenderTarget* target)
{
	//Set render texture
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);

	//Rendering
	this->tileMap.renderGameState  (this->renderTexture, this->player.getCenter(), &this->core_shader);  //Render tile map
	this->mapTrapsComponent.render (this->renderTexture);                                                //Render traps

	this->renderEnemies            ();                                                                   //Render all enemies
	this->player.render            (this->renderTexture, &this->core_shader);                            //Render player

	this->renderTexture.setView    (this->renderTexture.getDefaultView());                               //Seting view
	this->playerGUI.render         (this->renderTexture, this->guiRenderFlag);                           //Render player GUI

	if (this->paused && !this->skillMenuActive && !this->itemsMenuActive && !this->gameOverMenuActive) //Pause menu render
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
	else if (this->gameOverMenuActive)
	{
		this->gameOverMenu.render(this->renderTexture);
	}

	//Render renderTexure
	this->renderTexture.display();

	//Final rendering using render sprite
	target->draw(this->renderSprite);
}
