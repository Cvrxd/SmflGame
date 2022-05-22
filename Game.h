#pragma once
#include"MainMenuState.h"

class MainMenuState;

class Game
{
private:
	// Vriables
	// core
	sf::Clock dtClock;

	float dt;
	float gridSize;

	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::Event sfEvent;

	sf::RenderWindow* window = nullptr;
	std::stack<State*> states;
	std::unordered_map<std::string, int> supportedKeys;

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
