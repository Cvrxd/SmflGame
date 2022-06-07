#pragma once
#include "State.h"
#include "Gui.h"

class State;
class Button;
class DropDownList;

class SettingsState : public State
{
private:
	using MapButtons		= std::unordered_map<std::string, std::unique_ptr<GUI::Button>>;
	using MapDropDownLists	= std::unordered_map<std::string, std::unique_ptr<GUI::DropDownList>>;
	using VectorVideoModes	= std::vector<sf::VideoMode>;

	//Variables
	sf::Texture			backgroundTexture;
	sf::RectangleShape	background;
	sf::Font			font;
	sf::Text			optionsText;

	VectorVideoModes	videoModes;
	MapButtons			buttons;
	MapDropDownLists	dropDownLists;

	//Init functions
	void initVariables();
	void initText();
	void initBackground();
	void initFonts();
	void initGUI();
	void initKeybinds()								override;

public:
	SettingsState(StateData* state_data)			noexcept;
	virtual ~SettingsState();

	//Accessors

	//Functions
	void updateInput(const float& dt)				override;
	void updateGUI(const float& dt);
	void update(const float& dt)					override;
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr)	override;
};

