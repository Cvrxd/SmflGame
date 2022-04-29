#include "stdafx.h"
#include "Game.h"

// itialisation funcs

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::initWnodow()
{
	std::ifstream ifs("Configs/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}
	ifs.close();
	
	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if (this->fullscreen)
	{
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	}
	else
	{
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	}
	
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
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

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Game::Game()
{
	this->initWnodow();
	this->initKeys();
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

/////////////// GAME Functions ///////////////

void Game::endAplication()
{

}

//update
void Game::updateDt()
{
	// updates dt
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}  
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	// update states
	if (!this->states.empty())
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
	// aplications end
	else
	{
		this->endAplication();
		this->window->close();
	}
}

//render
void Game::render()
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
//