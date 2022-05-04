#pragma once
#include "PauseMenu.h"
#include "State.h"
#include "Gui.h"
#include "TileMap.h"

class State;
class PauseMenu;
class Button;
class TileMap;
class TextureSelector;

class EditorState : public State
{
private:
	//Variables 
	sf::Font font;
	sf::Text cursorText;

	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;

	PauseMenu* pauseMenu;
	TileMap* tileMap;
	GUI::TextureSelector* textureSelector;

	std::map<std::string, GUI::Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initTexts();
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
	void updateGUI(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt) override;

	void renderGUI(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL) override;
};

