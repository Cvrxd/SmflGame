#pragma once
#include "State.h"
#include "Gui.h"

class SettingsState : public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text optionsText;

	std::map<std::string, GUI::Button*> buttons;
	std::map<std::string, GUI::DropDownList*> dropDownLists;

	std::vector<sf::VideoMode> videoModes;

	//Functions
	void initVariables();
	void initText();
	void initBackground();
	void initFonts();
	void initGUI();
	void initKeybinds() override;

public:
	SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

	//Accessors

	//Functions
	void updateInput(const float& dt) override;
	void updateGUI(const float& dt);
	void update(const float& dt) override;
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL) override;
};

