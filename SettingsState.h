#pragma once
#include "State.h"
#include "Gui.h"

class State;
class Button;
class DropDownList;

class SettingsState : public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text optionsText;

	std::vector<sf::VideoMode> videoModes;

	std::unordered_map<std::string, GUI::Button*> buttons;
	std::unordered_map<std::string, GUI::DropDownList*> dropDownLists;

	//Functions
	void initVariables();
	void initText();
	void initBackground();
	void initFonts();
	void initGUI();
	void initKeybinds() override;

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	//Accessors

	//Functions
	void updateInput(const float& dt) override;
	void updateGUI(const float& dt);
	void update(const float& dt) override;
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL) override;
};

