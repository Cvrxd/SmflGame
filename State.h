#pragma once
#include"GraphicsSettings.h"
#include"Player.h"

struct GraphicsSettings;
class Player;
class State;

enum class STATE_TYPE {GAME_STATE = 0, SETTINGS_STATE, EDITOR_STATE, MAIN_MENU_STATE};

struct StateData
{
	using SupportedKeysMap = std::unordered_map<std::string, int>;
	using StatesStack      = std::stack<State*>;

	//Variables
	float               gridSize;
	sf::Font            font;
	GraphicsSettings*   gfxSettings;
	sf::RenderWindow*   window;
	SupportedKeysMap*   supportedKeys;
	StatesStack*        states;
};

class State
{
protected:
	using StatesStack   = std::stack<State*>;
	using KeysMap       = std::unordered_map<std::string, int>;
	using TexturesMap   = std::unordered_map<std::string, sf::Texture>;

	//State type
	STATE_TYPE type;

	//Core variables
	bool    quit;
	bool    paused;

	float   keyTime;
	float   keyTimeMax;
	float   gridSize;

	//Mouse positions
	sf::Vector2i    mousePosScreen;
	sf::Vector2i    mousePosWindow;
	sf::Vector2i    mousePosGrid;
	sf::Vector2f    mousPosView;

	//Keybinds and state data
	StatesStack*    states;
	StateData*      stateData;

	KeysMap*        supportedKeys;
	KeysMap         keybinds;

	//Resourses
	TexturesMap     textures;

	//Window
	sf::RenderWindow* window = nullptr;

	//Init functions
	virtual void initKeybinds () = 0;

	//Update functions
	virtual void updateKeyTime        (const float& dt);
	virtual void updateInput          (const float& dt) = 0;
	virtual void updateMousePosition  (sf::View* view = nullptr);

public:
	State (StateData* state_data) noexcept;
	virtual ~State();

	//Functions
	void pauseState     ();
	void unpausedState  ();
	
	//Accessors
	const STATE_TYPE& getStateType() const;

	const bool& getQuit     ()  const;
	const bool	getKeyTime  ();

	//End state
	virtual void endState   ();

	//Update, render
	virtual void updateTopState()                              = 0;

	virtual void update  (const float& dt)                     = 0;
	virtual void render  (sf::RenderTarget* target = nullptr)  = 0;
};

