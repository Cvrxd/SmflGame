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

	//To do
	struct MainMenuSounds
	{
		//Background music
		sf::SoundBuffer soundBuffer;
		sf::Music music;

		//Click sound
		std::pair<sf::SoundBuffer, sf::Sound> clickSound;
	};

	//variables 
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	std::unordered_map<std::string, std::unique_ptr<GUI::Button>> buttons;

	//Sounds
	MainMenuSounds sounds;

	//Init functions
	void initVariables();
	void initSounds();
	void initBackground();
	void initFonts();
	void initButtons();
	void initKeybinds() override;

public:
	MainMenuState(StateData* state_data) noexcept;
	virtual ~MainMenuState() override;

	//Functions
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL) override;
};

