#include "stdafx.h"
#include "SettingsState.h"

#define UPDATE_DROP_DOWN_LIST_OFFSET this->offsetYforDropDownLists += 90.f

//Initialisation functions
inline void SettingsState::initVariables()
{
	this->videoModes = std::move(sf::VideoMode::getFullscreenModes());
}

inline void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 250.f)); 
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		" Resolution \n\n\n Fullscreen \n\n\n Vsync \n\n\n Frame limit"
	);
}

inline void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Textures/background/mainmenu_background.png"))
	{
		throw("Failed to load background main menu");
	}
	this->background.setTexture(&this->backgroundTexture);
}

inline void SettingsState::initKeybinds()
{
	std::ifstream ifs("Configs/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key_value = "";

		while (ifs >> key >> key_value)
		{
			this->keybinds[key] = this->supportedKeys->at(key_value);
		}
	}

	ifs.close();
}

inline void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

inline void SettingsState::initGUI()
{
	this->buttons["EXIT_STATE"] = std::make_unique<GUI::Button>(815.f, 850.f, 180.f, 75.f,
		&this->font, "Quit", 50,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = std::make_unique<GUI::Button>(800.f, 700.f, 180.f, 75.f,
		&this->font, "Apply", 50,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	//Drop down lists
	this->dropDownLists.reserve(7);

	std::vector<std::string> video_modes_str;

	video_modes_str.reserve(this->videoModes.size());

	for (auto& el : this->videoModes)
	{
		video_modes_str.push_back(std::to_string(el.width) + " x " + std::to_string(el.height));
	}

	this->dropDownLists["RESOLUTION"] = std::make_unique<GUI::DropDownList>(350, 225 + this->offsetYforDropDownLists, 200, 50, font, video_modes_str.data(),
		static_cast<unsigned int>(video_modes_str.size()), 0);

	UPDATE_DROP_DOWN_LIST_OFFSET;
	
	std::string text_list[] = { "ON" , "OFF" };

	this->dropDownLists["FULLSCREEN"] = std::make_unique<GUI::DropDownList>(350, 225 + this->offsetYforDropDownLists, 200, 50, font, text_list,
		static_cast<unsigned int>(text_list->length()), 0);
	
	UPDATE_DROP_DOWN_LIST_OFFSET;

	this->dropDownLists["VSYNC"] = std::make_unique<GUI::DropDownList>(350, 225 + this->offsetYforDropDownLists, 200, 50, font, text_list,
		static_cast<unsigned int>(text_list->length()), 0);

	UPDATE_DROP_DOWN_LIST_OFFSET;

	std::string frame_limits[] = { "120" , "60", "30" };

	this->dropDownLists["FRAME_LIMIT"] = std::make_unique<GUI::DropDownList>(350, 225 + this->offsetYforDropDownLists, 200, 50, font, frame_limits,
		static_cast<unsigned int>(frame_limits->length()), 0);
}

//Constructor
SettingsState::SettingsState(StateData* state_data) noexcept
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();	  //init fonts 
	this->initKeybinds(); //init key binds from ini
	this->initGUI();  //init gui
	this->initText();
}

SettingsState::~SettingsState()
{
}

//Accessors

//Functions
inline void SettingsState::updateInput(const float& dt)
{

}

inline void SettingsState::updateGUI(const float& dt)
{
	//updates all buttons
	for (auto& el : this->buttons)
	{
		el.second->update(this->mousePosWindow);
	}

	//update drop down list
	for (auto& el : this->dropDownLists)
	{
		el.second->update(this->mousePosWindow, dt);
	} 

	//Apply selected changes
	if (this->buttons["APPLY"]->isPressed())
	{
		if(this->stateData->gfxSettings->resolution != this->videoModes[this->dropDownLists["RESOLUTION"]->getActiveBoxId()]);
		{
			this->stateData->gfxSettings->resolution = this->videoModes[this->dropDownLists["RESOLUTION"]->getActiveBoxId()];
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
		}
		
	}

	//Quit state
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void SettingsState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePosition();
	this->updateGUI(dt);
}

inline void SettingsState::renderGUI(sf::RenderTarget& target)
{
	//render buttons
	for (auto& el : this->buttons)
	{
		el.second->render(target);
	}

	//render drop down list
	for (auto& el : this->dropDownLists)
	{
		el.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->optionsText);

	this->renderGUI(*target);

	//REMOVE LATER JUST DEBUG!!!
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousPosView.x, this->mousPosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	mouseText.setString(std::to_string(this->mousPosView.x) + " " + std::to_string(this->mousPosView.y));

	target->draw(mouseText);*/
}