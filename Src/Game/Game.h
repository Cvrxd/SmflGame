#pragma once
#include<States/MainMenuState/MainMenuState.h>

class MainMenuState;

class Game
{
private:
	using KeyBindsMap   = std::unordered_map<std::string, int>;
	using StatesStack   = std::stack<std::unique_ptr<State>>;

	//Vriables
	float               dt;
	float               gridSize;

	GraphicsSettings    gfxSettings;
	StateData           stateData;
	StatesStack         states;
	KeyBindsMap         supportedKeys;

	sf::Clock           dtClock;
	sf::Event           sfEvent;
	sf::RenderWindow*   window;

	//Init functions
	void initVariables         ();
	void initGraphicsSettings  ();
	void initWnodow            ();
	void initKeys              ();
	void initStateData         ();
	void initStates            ();

	//Update functions
	void updateDt          ();
	void updateSFMLEvents  ();
	void update            ();

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
