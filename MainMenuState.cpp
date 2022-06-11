#include "stdafx.h"
#include "MainMenuState.h"

//Initialisation
inline void MainMenuState::initVariables()
{
}

inline void MainMenuState::initSounds()
{
	//Init background music
	this->sounds.music.openFromFile("Sounds/main_menu/main_menu.ogg");
	this->sounds.music.setVolume(5.f);
	this->sounds.music.setLoop(true);
	
	//Play background music
	this->sounds.music.play();

	//Click sound
	this->sounds.clickSound.first.loadFromFile("Sounds/main_menu/click.wav");
	this->sounds.clickSound.second.setBuffer(this->sounds.clickSound.first);
	this->sounds.clickSound.second.setVolume(10.f);
}

inline void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Textures/background/mainmenu_background.png"))
	{
		throw("Failed to load background main menu");
	}
	this->background.setTexture(&this->backgroundTexture); 
}

inline void MainMenuState::initKeybinds()
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

inline void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

inline void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = std::make_unique<GUI::Button>(100.f, 100.f, 300.f, 70.f,
		&this->font, "New Game", 70,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SETTINGS_STATE"] = std::make_unique<GUI::Button>(100.f, 250.f, 300.f, 70.f,
		&this->font, "Settings", 70,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EDITOR_STATE"] = std::make_unique<GUI::Button>(100.f, 400.f, 250.f, 70.f,
		&this->font, "Editor", 70,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EXIT_STATE"] = std::make_unique<GUI::Button>(100.f, 550.f, 180.f, 75.f,
		&this->font, "Quit", 70,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
	
}

//Update functions
inline void MainMenuState::updateInput(const float& dt)
{

}

inline void MainMenuState::updateButtons()
{
	//updates all buttons
	for (auto& el : this->buttons)
	{
		el.second->update(this->mousePosWindow);
	}

	//New game start
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->sounds.clickSound.second.play();

		this->states->push(new GameState(this->stateData));
		this->sounds.music.stop();
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->sounds.clickSound.second.play();

		this->states->push(new SettingsState(this->stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->sounds.clickSound.second.play();

		this->states->push(new EditorState(this->stateData));
	}

	//Quit game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->sounds.clickSound.second.play();

		this->sounds.music.stop();
		this->endState();
	}
}

//Render functions
inline void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& el : this->buttons)
	{
		el.second->render(target);
	}
}

//Constructor
MainMenuState::MainMenuState(StateData* state_data) noexcept
	: State(state_data)
{
	this->initVariables();
	this->initSounds();
	this->initBackground();
	this->initFonts();	   
	this->initKeybinds(); 
	this->initButtons(); 
}

MainMenuState::~MainMenuState()
{
}

//Oublic functions 
void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePosition();
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	this->renderButtons(*target);

	//REMOVE LATER JUST DEBUG!!!
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousPosView.x, this->mousPosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	mouseText.setString(std::to_string(this->mousPosView.x) + " " + std::to_string(this->mousPosView.y));

	target->draw(mouseText);*/
}