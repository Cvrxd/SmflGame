#pragma once
#include"MainMenuState.h"

class MainMenuState;

class Game
{
private:
	// Vriables

	// core
	StateData stateData;

	GraphicsSettings gfxSettings;
	sf::RenderWindow* window = nullptr;
	sf::Event sfEvent;
		
	sf::Clock dtClock;
	float dt;
	float gridSize;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	// functions
	void initVariables();
	void initGraphicsSettings();
	void initWnodow();
	void initKeys();
	void initStateData();
	void initStates();
public:
	Game();
	~Game();

	//Functions
	void endAplication();

	
	//update
	void updateSFMLEvents();
	void update();

	//render
	void render();
	void updateDt();

	//core
	void run();
};
