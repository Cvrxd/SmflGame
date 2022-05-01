#pragma once
#include "PauseMenu.h"
#include "State.h"
#include "Gui.h"
#include "TileMap.h"

class State;
class PauseMenu;
class Button;
class TileMap;

class EditorState : public State
{
private:
	//variables 
	sf::Font font;
	PauseMenu* pauseMenu;

	std::map<std::string, GUI::Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape selectorRect;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();
	void initPauseMenu();
	void initKeybinds() override;
	void initGUI();
	void initTileMap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState() override;

	//functions
	void updateInput(const float& dt) override;
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGUI();
	void updatePauseMenuButtons();
	void update(const float& dt) override;

	void renderGUI(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL) override;
};

