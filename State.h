#pragma once
#include"GraphicsSettings.h"
#include"Player.h"

struct GraphicsSettings;
class Player;
class State;

struct StateData
{
	StateData()
	{

	}

	//Variables
	float gridSize;
	GraphicsSettings* gfxSettings;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
protected:
	//Core variables
	std::stack<State*>* states;
	
	StateData* stateData;
	
	sf::RenderWindow* window = nullptr;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	float gridSize;

	bool quit;
	bool paused;

	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousPosView; 
	sf::Vector2i mousePosGrid;

	//Resourses
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	//Functions
	void pauseState();
	void unpausedState();
	
	//Accessors
	const bool& getQuit() const;
	const bool getKeyTime();
 
	// end state
	virtual void endState();

	// update functions
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePosition(sf::View* view = NULL);

	virtual void update(const float& dt) = 0;;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

