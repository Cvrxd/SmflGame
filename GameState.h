#pragma once
#include "State.h"
#include "PauseMenu.h"

class GameState : public State
{
private:
	//variables 
	sf::Font font;
	PauseMenu* pauseMenu;

	Player* player;

	//Functions
	void initFonts();
	void initKeybinds() override;
	void initTextures();
	void initPauseMenu();
	void initPlayers();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState() override;

	//functions
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

