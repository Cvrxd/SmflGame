#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class PauseMenu;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState : public State
{
private:
	//variables 
	sf::View view;
	sf::Font font;

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	PauseMenu* pauseMenu;

	Player* player;
	TileMap* tileMap;

	//Functions
	void initRenderTextures();
	void initView();
	void initFonts();
	void initKeybinds() override;
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();
public:
	GameState(StateData* state_data);
	virtual ~GameState() override;

	//functions
	void updateView(const float& dt);
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt) override;
	void updateTileMap(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

