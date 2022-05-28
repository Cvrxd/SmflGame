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
	//variables 
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	std::unordered_map<std::string, GUI::Button*> buttons;

	//Sounds
	sf::SoundBuffer soundBuffer;
	sf::Music music;

	//Functions
	void initVariables();
	void initSounds();
	void initBackground();
	void initFonts();
	void initButtons();
	void initKeybinds() override;
public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState() override;

	//Functions
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL) override;
};

