#include "stdafx.h"
#include "SettingsState.h"

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
		"Resolution \n\nFullscreen \n\nVsync \n\nAntializating"
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
	this->buttons["EXIT_STATE"] = new GUI::Button(815.f, 850.f, 180.f, 75.f,
		&this->font, "Quit", 50,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = new GUI::Button(800.f, 700.f, 180.f, 75.f,
		&this->font, "Apply", 50,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	//Resolution list
	std::vector<std::string> modes_str;

	modes_str.reserve(this->videoModes.size());

	for (auto& el : this->videoModes)
	{
		modes_str.push_back(std::to_string(el.width) + " x " + std::to_string(el.height));
	}

	std::string text_list[] = { "1920 x 1080", "800 x 600", "640 x 480" };
	this->dropDownLists["RESOLUTION"] =  new GUI::DropDownList(280, 225, 200, 50, font, modes_str.data(), 
		static_cast<unsigned int>(modes_str.size()), 0);
	//

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
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	} 
	
	for (auto it = this->dropDownLists.begin(); it != dropDownLists.end(); ++it)
	{
		delete it->second;
	}
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
		//Test
		this->stateData->gfxSettings->resolution = this->videoModes[this->dropDownLists["RESOLUTION"]->getActiveBoxId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
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