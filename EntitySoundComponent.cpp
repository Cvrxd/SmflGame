#include "stdafx.h"
#include "EntitySoundComponent.h"

//Constructors
EntitySoundComponent::EntitySoundComponent() noexcept
	:movementSound(nullptr)
{
}

EntitySoundComponent::~EntitySoundComponent()
{
}

//Functions
void EntitySoundComponent::addWalkingSound(const std::string& path)
{
	this->sounds["WALKING"].first.loadFromFile(path);
	this->sounds["WALKING"].second.setBuffer(this->sounds["WALKING"].first);
	this->sounds["WALKING"].second.setVolume(0.5f);
	this->sounds["WALKING"].second.setLoop(true);

	this->movementSound = &this->sounds["WALKING"].second;

	this->movementSound->play();
	this->movementSound->pause();
}

void EntitySoundComponent::addRunningSound(const std::string& path)
{
	this->sounds["RUNNING"].first.loadFromFile(path);
	this->sounds["RUNNING"].second.setBuffer(this->sounds["RUNNING"].first);
	this->sounds["RUNNING"].second.setVolume(0.5f);
	this->sounds["RUNNING"].second.setLoop(true);

	this->sounds["RUNNING"].second.play();
	this->sounds["RUNNING"].second.pause();
}

void EntitySoundComponent::changeMovementSound(const bool& running)
{
	if (running)
	{
		if (this->movementSound != &this->sounds["RUNNING"].second)
		{
			this->movementSound = &this->sounds["RUNNING"].second;
			this->sounds["WALKING"].second.pause();
		}
	}
	else
	{
		if (this->movementSound != &this->sounds["WALKING"].second)
		{
			this->movementSound = &this->sounds["WALKING"].second;
			this->sounds["RUNNING"].second.pause();
		}
	}
}

void EntitySoundComponent::changeMovementVolume(const bool& increase)
{
	if (increase)
	{
		if (this->movementSound->getVolume() != 0.5f)
		{
			this->movementSound->setVolume(0.5f);
		}
	}
	else
	{
		if (this->movementSound->getVolume() != 0.2f)
		{
			this->movementSound->setVolume(0.2f);
		}
	}
}

void EntitySoundComponent::pauseMovementSound()
{
	this->movementSound->pause();
}

void EntitySoundComponent::unpauseMovementSound()
{
	if (this->movementSound->getStatus() == sf::Sound::Paused)
	{
		this->movementSound->play();
	}
}
