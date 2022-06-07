#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "BossEnemy.h"
#include "MeleEnemy.h"
#include "MageEnemy.h"
#include "DestroyingEnemy.h"

class State;
class PauseMenu;
class TileMap;
class PlayerGUI;
class Enemy;
class BossEnemy;
class MeleEnemy;
class MageEnemy;
class DestroyingEnemy;

class GameState : public State
{
private:
	//variables 
	bool skillMenuActive = false;
	bool itemsMenuActive = false;

	//Player buff
	bool isBuffed = false;

	//Core
	sf::RenderTexture	renderTexture;
	sf::Sprite			renderSprite;
	sf::Vector2i		viewGridPosition;

	sf::View	view;
	sf::Font	font;
	sf::Shader	core_shader;

	PlayerGUI	playerGUI;
	SkillsMenu	skillsMenu;
	ItemsMune	itemsMenu;
	PauseMenu	pauseMenu;
	TileMap		tileMap;
	Player		player;

	//Entities
	std::vector<BossEnemy>			bosses;
	std::vector<MeleEnemy>			meleEnemies;
	std::vector<MageEnemy>			mageEnemies;
	std::vector<DestroyingEnemy>	destroyingEnemies;

	//Sounds
	EnemySoundBox	enemiesSounds;
	GuiSoundsBox	guiSounds;

	//Init functions
	void initRenderTextures();
	void initView();
	void initFonts();
	void initKeybinds() override;
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayers();
	void initEnemies();
	void initPlayerGUI();
	void initTileMap();
	void initSounds();

	//Update functions
	void updateView(const float& dt);
	void updatePauseMenuButtons();
	void updateEnemies(const float& dt);
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt) override;
	void updateTileMap(const float& dt);

	//Render functions
	void renderEnemies(sf::RenderTarget* target);

public:
	GameState(StateData* state_data);
	virtual ~GameState() override;

	//Functions
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};
