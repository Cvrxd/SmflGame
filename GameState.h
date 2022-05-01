#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class PauseMenu;
class TileMap;

class GameState : public State
{
private:
	//variables 
	sf::Font font;
	PauseMenu* pauseMenu;

	Player* player;
	TileMap* tileMap;

	//Functions
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
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

