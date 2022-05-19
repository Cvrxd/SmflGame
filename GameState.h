#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "BossEnemy.h"

class State;
class PauseMenu;
class TileMap;
class PlayerGUI;
class Enemy;
class BossEnemy;

class GameState : public State
{
private:
	//Entities
	std::vector<BossEnemy> bosses;

	//variables 
	sf::Shader core_shader;

	sf::View view;
	sf::Vector2i viewGridPosition;

	sf::Font font;

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	TileMap tileMap;
	Player player;

	PauseMenu pauseMenu;
	PlayerGUI playerGUI;
	SkillsMenu skillsMenu;
	bool skillMenuActive;

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

