#include "stdafx.h"
#include "State.h"

//Initialisation funcs
State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: window(window), supportedKeys(supportedKeys), states(states), quit(false), paused(false), keyTime(0.f), keyTimeMax(10.f)
{

}

State::~State()
{
}

// PauseMenu functions
void State::pauseState()
{
	this->paused = true;
}

void State::unpausedState()
{
	this->paused = false;
}

//Accessors
const bool& State::getQuit() const
{
	return this->quit;
}

const bool& State::getKeyTime()
{
	return this->keyTime >= this->keyTimeMax;
}

//Other Functions
void State::endState()
{
	this->quit = true;
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 100.f * dt;
	}
	else
	{
		this->keyTime = 0;
	}
}

//Mouse position update
void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousPosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
