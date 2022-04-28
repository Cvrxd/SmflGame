#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class MainMenuState : public State
{
private:
	//variables 
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, GUI::Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();
	void initKeybinds() override;
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState() override;

	//Functions
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL) override;
};

