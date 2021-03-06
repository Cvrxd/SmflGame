#pragma once
#include <States/State.h>
#include <Gui/GeneralGui/Gui.h>

class State;
class Button;
class DropDownList;

class SettingsState : public State
{
private:
	using ButtonsMap        = std::unordered_map<std::string, std::unique_ptr<GUI::Button>>;
	using DropDownListsMap  = std::unordered_map<std::string, std::unique_ptr<GUI::DropDownList>>;
	using VidoModesVector   = std::vector<sf::VideoMode>;
	using FrameLimitsVector = std::vector<unsigned int>;
	using ActiveBoxPtr      = std::unique_ptr<GUI::DropDownList>*;
	//Variables
	float offsetYforDropDownLists = 0.f;

	sf::Texture         backgroundTexture;
	sf::RectangleShape  background;
	sf::Font            font;
	sf::Text            optionsText;

	VidoModesVector     videoModes;
	FrameLimitsVector   frameLimits;
	ButtonsMap          buttons;
	DropDownListsMap    dropDownLists;
	ActiveBoxPtr        activeDropDownList;

	//Init functions
	void initVariables   ();
	void initText        ();
	void initBackground  ();
	void initFonts       ();
	void initGUI         ();
	void initKeybinds    ()                   override;

	//Update functions
	void updateGuiPosition();

public:
	SettingsState (StateData* state_data)     noexcept;
	virtual ~SettingsState();

	//Functions
	void updateTopState()                                    override;

	void updateInput  (const float& dt)                      override;
	void updateGUI    (const float& dt);
	void update       (const float& dt)                      override;
	void renderGUI    (sf::RenderTarget& target);
	void render       (sf::RenderTarget* target = nullptr)   override;
};

