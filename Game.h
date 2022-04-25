#pragma once

#include"MainMenuState.h"

class Game
{
private:
	// Vriables
	// core
	sf::RenderWindow* window = nullptr;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	// functions
	void initVariables();
	void initWnodow();
	void initKeys();
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
