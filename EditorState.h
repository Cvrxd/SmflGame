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
	using MapButtons            = std::unordered_map<std::string, std::unique_ptr<GUI::Button>>;
	using TextureSelectorUptr   = std::unique_ptr<GUI::TextureSelector>;

	//Variables 
	float   cameraSpeed;

	bool    collision;
	short   tileType;

	sf::View view;

	sf::Font font;
	sf::Text cursorText;

	sf::RectangleShape  sidebar;
	sf::RectangleShape  selectorRect;
	sf::IntRect         textureRect;
	
	TextureSelectorUptr textureSelector;
	PauseMenu           pauseMenu;
	MapButtons          buttons;
	TileMap             tileMap;

	//Init functions
	void initVariables   ();
	void initView        ();
	void initBackground  ();
	void initFonts       ();
	void initTexts       ();
	void initButtons     ();
	void initPauseMenu   ();
	void initKeybinds    ()                           override;
	void initGUI         ();

	//Update functions
	void updateView              (const float& dt);
	void updateInput             (const float& dt)	  override;
	void updateEditorInput       (const float& dt);
	void updateButtons           ();
	void updateGUI               (const float& dt);
	void updatePauseMenuButtons  ();

	//Render functions
	void renderGUI      (sf::RenderTarget& target);
	void renderButtons  (sf::RenderTarget& target);

public:
	EditorState (StateData* state_data)               noexcept;
	virtual ~EditorState();

	//Functions
	void updateTopState()                            override;

	void update  (const float& dt)                    override;
	void render  (sf::RenderTarget* target = nullptr) override;
};

