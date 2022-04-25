#include "MainMenuState.h"

///////// Initialisation //////////

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Textures/background/mainmenu_background.png"))
	{
		throw("Failed to load background main menu");
	}
	this->background.setTexture(&this->backgroundTexture); 
}

// Keybinds init from ini
void MainMenuState::initKeybinds()
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

//fonts
void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

//buttons init
void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	);

	this->buttons["SETTINGS"] = new Button(100, 200, 150, 50,
		&this->font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	);

	this->buttons["EXIT_STATE"] = new Button(100, 300, 150, 50,
		&this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	);
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();	  //init fonts 
	this->initKeybinds(); //init key binds from ini
	this->initButtons();  //init buttons 
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

// Functions 
 
// update
void MainMenuState::updateInput(const float& dt)
{ 
	
}

void MainMenuState::updateButtons()
{
	//updates all buttons
	for (auto& el : this->buttons)
	{
		el.second->update(this->mousPosView);
	}

	//New game start
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Quit game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePosition();
	this->updateButtons();
}

//render
void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& el : this->buttons)
	{
		el.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	this->renderButtons(target);

	//REMOVE LATER JUST DEBUG!!!
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousPosView.x, this->mousPosView.y - 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	mouseText.setString(std::to_string(this->mousPosView.x) + " " + std::to_string(this->mousPosView.y));

	target->draw(mouseText);*/
}