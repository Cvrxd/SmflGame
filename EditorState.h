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
	float cameraSpeed;
	sf::View view;

	sf::Font font;
	sf::Text cursorText;

	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;
	GUI::TextureSelector* textureSelector;

	PauseMenu pauseMenu;
	std::unordered_map<std::string, GUI::Button*> buttons;

	TileMap tileMap;
	bool collision;
	short tileType;

	//Functions
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initTexts();
	void initButtons();
	void initPauseMenu();
	void initKeybinds() override;
	void initGUI();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState() override;

	//functions
	void updateView(const float& dt);
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

