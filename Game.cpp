#include "stdafx.h"
#include "Game.h"

//Itialisation
inline void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->gridSize = 54.f;
}

inline void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Configs/graphics.ini");
}

inline void Game::initWnodow()
{
	if (this->gfxSettings.fullscreen)
	{
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title,
			sf::Style::Fullscreen, this->gfxSettings.contextSettings);
	}
	else
	{
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, 
			sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
	}
	
	this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vertucalSync);
}

inline void Game::initKeys()
{
	std::ifstream ifs("Configs/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();
	 
	//Debug
	for (auto& el : this->supportedKeys)
	{
		std::cout << el.first << " " << el.second <<"\n";
	}
}

inline void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.states = &this->states;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.gridSize = this->gridSize;
	if (!this->stateData.font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

inline void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

//Constructor
Game::Game() noexcept
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWnodow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		states.pop();
	}
}

//Functions
void Game::endAplication()
{

}

inline void Game::updateDt()
{
	// updates dt
	this->dt = this->dtClock.restart().asSeconds();
}

inline void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}  
	}
}

inline void Game::update()
{
	this->updateSFMLEvents();

	// update states
	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(dt);

			if (this->states.top()->getQuit())
			{
				// some stuff like saving the game
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	// aplications end
	else
	{
		this->endAplication();
		this->window->close();
	}
}

inline void Game::render()
{
	this->window->clear();
	
	//render states
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
