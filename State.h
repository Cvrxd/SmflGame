#pragma once
#include"GraphicsSettings.h"
#include"Player.h"

struct GraphicsSettings;
class Player;
class State;

struct StateData
{
	using mapSupportedKeys = std::unordered_map<std::string, int>;
	
	//Variables
	float				gridSize;
	sf::Font			font;
	GraphicsSettings*	gfxSettings;
	sf::RenderWindow*	window;
	mapSupportedKeys*	supportedKeys;
	std::stack<State*>*	states;
};

class State
{
protected:
	using StatesStack	= std::stack<State*>;
	using KeysMap		= std::unordered_map<std::string, int>;
	using TexturesMap	= std::map<std::string, sf::Texture>;

	//Core variables
	bool	quit;
	bool	paused;

	float	keyTime;
	float	keyTimeMax;
	float	gridSize;

	//Mouse positions
	sf::Vector2i	mousePosScreen;
	sf::Vector2i	mousePosWindow;
	sf::Vector2i	mousePosGrid;
	sf::Vector2f	mousPosView;

	//Keybinds and state data
	StatesStack*	states;
	StateData*		stateData;

	KeysMap*		supportedKeys;
	KeysMap			keybinds;

	//Resourses
	TexturesMap		textures;

	//Window
	sf::RenderWindow* window = nullptr;

	//Init functions
	virtual void initKeybinds() = 0;

	//Update functions
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePosition(sf::View* view = nullptr);

public:
	State(StateData* state_data) noexcept;
	virtual ~State();

	//Functions
	void pauseState();
	void unpausedState();
	
	//Accessors
	const bool& getQuit() const;
	const bool	getKeyTime();
 
	//End state
	virtual void endState();

	virtual void update(const float& dt) = 0;;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

