#pragma once
#include <States/GameState/GameState.h>
#include <States/EditorState/EditorState.h>
#include <States/SettingsState/SettingsState.h>
#include <Gui/GeneralGui/Gui.h>

class GameState;
class EditorState;
class SettingsState;
class Button;

class MainMenuState : public State
{
private:
	using TextsMap       = std::unordered_map<std::string, sf::Text>;
	using ButtonsMap     = std::unordered_map<std::string, std::unique_ptr<GUI::Button>>;
	using SpitesPair     = std::pair<sf::Sprite, sf::Sprite>;
	using AnimationsPair = std::pair<AnimationComponent, AnimationComponent>;

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
	sf::Text            recordText;

	//Animations
	AnimationsPair crystalsAnimations;
	SpitesPair     crystalsSprites;
	sf::Texture    crystalsTexture;
	std::string    crystalsAnimationKey = "NORMAL";

	//Record info
	RecordInfo          normalRecordInfo;
	RecordInfo          hardRecordInfo;
	RecordInfo          insaneRecordInfo;

	//GUI
	ButtonsMap          buttons;
	TextsMap            recordTexts;

	//Sounds
	MainMenuSounds      sounds;

	//Threads
	sf::Thread updateGuiThread;

	//Init functions
	void initVariables    ();
	void initTextures     ();
	void initAnimations   ();
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
	void updateAnimations (const float& dt);
	void updateGUI        ();
	void updateText       ();

	//Render functions
	void renderGUI        (sf::RenderTarget& target);
	void renderRecordInfo (sf::RenderTarget& target);

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

