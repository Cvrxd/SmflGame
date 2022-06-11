#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class GameState;
class EditorState;
class SettingsState;
class Button;

class MainMenuState : public State
{
private:
	using ButtonsMap          = std::unordered_map<std::string, std::unique_ptr<GUI::Button>>;

	struct MainMenuSounds
	{
		using Sound = std::pair<sf::SoundBuffer, sf::Sound>;

		//Background music
		sf::SoundBuffer soundBuffer;
		sf::Music       music;

		//Click sound
		Sound           clickSound;
	};

	//Variables 
	sf::Font            font;
	sf::Texture         backgroundTexture;
	sf::RectangleShape  background;

	//Buttons
	ButtonsMap          buttons;

	//Sounds
	MainMenuSounds      sounds;

	//Init functions
	void initVariables   ();
	void initSounds      ();
	void initBackground  ();
	void initFonts       ();
	void initButtons     ();
	void initKeybinds    ()                           override;

	//Update functions
	void updateInput     (const float& dt)            override;
	void updateButtons   ();

	//render functions
	void renderButtons   (sf::RenderTarget& target);

public:
	MainMenuState (StateData* state_data)              noexcept;
	virtual ~MainMenuState()                           override;

	//Functions
	void update  (const float& dt)                     override;
	void render  (sf::RenderTarget* target = nullptr)  override;
};

