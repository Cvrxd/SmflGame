#pragma once
#include"MainMenuState.h"

class MainMenuState;

class Game
{
private:
	//Vriables
	float dt;
	float gridSize;

	sf::Clock dtClock;

	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::Event sfEvent;

	sf::RenderWindow* window = nullptr;
	std::stack<State*> states;
	std::unordered_map<std::string, int> supportedKeys;

	//Init functions
	void initVariables();
	void initGraphicsSettings();
	void initWnodow();
	void initKeys();
	void initStateData();
	void initStates();

	//Update functions
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render functions
	void render();

	//Core functions
	void endAplication();

public:
	Game() noexcept;
	~Game();

	//Functions
	void run();
};
