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
	bool skillMenuActive;
	bool isBuffed = false;

	sf::Vector2i viewGridPosition;

	sf::View view;
	sf::Font font;
	sf::Shader core_shader;

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	PlayerGUI playerGUI;
	SkillsMenu skillsMenu;
	PauseMenu pauseMenu;

	TileMap tileMap;
	Player player;

	//Entities
	std::vector<BossEnemy> bosses;
	std::vector<MeleEnemy> meleEnemies;
	std::vector<MageEnemy> mageEnemies;
	std::vector<DestroyingEnemy> destroyingEnemies;

	//Enemies sounds
	EnemiesSounds enemiesSounds;

	//Functions
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

public:
	GameState(StateData* state_data);
	virtual ~GameState() override;

	//functions
	void updateView(const float& dt);
	void updatePauseMenuButtons();
	void updateEnemies(const float& dt);
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt) override;
	void updateTileMap(const float& dt);
	void update(const float& dt) override;
	void renderEnemies(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = nullptr) override;
};
