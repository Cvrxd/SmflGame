#include <stdafx.h>
#include <Game/Game.h>

//Itialisation
inline void Game::initVariables()
{
	this->window    = nullptr;
	this->dt        = 0.f;
	this->gridSize  = 64.f;
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
}

inline void Game::initStateData()
{
	//Core variables
	this->stateData.dt             = &this->dt;
	this->stateData.window         = this->window;
	this->stateData.states         = &this->states;
	this->stateData.supportedKeys  = &this->supportedKeys;
	this->stateData.gfxSettings    = &this->gfxSettings;
	this->stateData.gridSize       = this->gridSize;

	//Loading font
	if (!this->stateData.font.loadFromFile("Fonts/Greybeard.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

inline void Game::initStates()
{
	this->states.push(std::make_unique<MainMenuState>(&this->stateData));
}

//Update functions
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
				//Deliting top state
				this->states.top()->endState();
				this->states.pop();
				
				//Update new top state after deleting previous top state
				if (!this->states.empty())
				{
					this->states.top()->updateTopState();
				}
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

//Render functions
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

//Core functions
inline void Game::endAplication()
{

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

		states.pop();
	}
}

//Public Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
