#pragma once
#include "State.h"
class GameState : public State
{
private:
	//variables 
	Player* player;

	//Functions
	void initKeybinds() override;
	void initTextures();
	void initPlayers();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState() override;

	//functions
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

