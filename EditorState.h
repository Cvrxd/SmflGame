#pragma once
#include "State.h"
#include "Gui.h"

class EditorState : public State
{
private:
	//variables 
	sf::Font font;

	std::map<std::string, GUI::Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();
	void initKeybinds() override;
public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~EditorState() override;

	//functions
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL) override;
};

