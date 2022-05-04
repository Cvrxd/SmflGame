#include "stdafx.h"
#include "State.h"

//Initialisation funcs
State::State(StateData* state_data)
	: stateData(state_data), window(state_data->window), supportedKeys(state_data->supportedKeys), states(state_data->states), gridSize(state_data->gridSize),
	  quit(false), paused(false), keyTime(0.f), keyTimeMax(10.f)
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

const bool State::getKeyTime()
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
void State::updateMousePosition(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
	{
		this->window->setView(*view);
	}
	
	this->mousPosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = static_cast<sf::Vector2u>(this->mousPosView / this->gridSize);

	this->window->setView(this->window->getDefaultView());
}
