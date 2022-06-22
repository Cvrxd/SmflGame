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
	using TextsMap    = std::unordered_map<std::string, sf::Text>;
	using ButtonsMap  = std::unordered_map<std::string, std::unique_ptr<GUI::Button>>;

	//Main menu sounds
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
	unsigned int        difficultyLvl = 1;

	sf::Font            font;
	sf::Texture         backgroundTexture;
	sf::RectangleShape  background;

	sf::Text            difficultyText;
	sf::Text            difficultyLvlText;

	//Record info
	RecordInfo          normalRecordInfo;
	RecordInfo          hardRecordInfo;
	RecordInfo          insaneRecordInfo;

	//GUI
	ButtonsMap          buttons;
	TextsMap            texts;

	//Sounds
	MainMenuSounds      sounds;

	//Init functions
	void initVariables    ();
	void initSounds       ();
	void initBackground   ();
	void initFonts        ();
	void initGUI          ();
	void initRecrodsInfo  ();
	void initKeybinds     ()                           override;

	//Player record info load and save
	void loadRecordInfo   ();
	void saveRecordInfo   ();

	//Update functions
	void updateInput      (const float& dt)            override;
	void updateGUI        ();
	void updateText       ();
	void updateRecordInfo ();

	//Eender functions
	void renderGUI       (sf::RenderTarget& target);

public:
	MainMenuState (StateData* state_data)              noexcept;
	virtual ~MainMenuState()                           override;

	//Functions
	void updateTopState()                              override;

	void updateGuiPosition();
	void playMusic();

	void update  (const float& dt)                     override;
	void render  (sf::RenderTarget* target = nullptr)  override;
};

