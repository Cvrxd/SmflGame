#include "stdafx.h"
#include "SoundComponent.h"

//Constructors
PlayerSoundBox::PlayerSoundBox() noexcept
	:movementSound(nullptr)
{
}

PlayerSoundBox::~PlayerSoundBox()
{
}

//Functions
void PlayerSoundBox::addWalkingSound(const std::string& path)
{
	this->sounds["WALKING"].first.loadFromFile(path);
	this->sounds["WALKING"].second.setBuffer(this->sounds["WALKING"].first);
	this->sounds["WALKING"].second.setVolume(this->movementVolumeMin);
	this->sounds["WALKING"].second.setLoop(true);

	this->movementSound = &this->sounds["WALKING"].second;

	this->movementSound->play();
	this->movementSound->pause();
}

void PlayerSoundBox::addRunningSound(const std::string& path)
{
	this->sounds["RUNNING"].first.loadFromFile(path);
	this->sounds["RUNNING"].second.setBuffer(this->sounds["RUNNING"].first);
	this->sounds["RUNNING"].second.setVolume(this->movementVolumeMin);
	this->sounds["RUNNING"].second.setLoop(true);

	this->sounds["RUNNING"].second.play();
	this->sounds["RUNNING"].second.pause();
}

void PlayerSoundBox::changeMovementSound(const bool& running)
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

void PlayerSoundBox::changeMovementVolume(const bool& increase)
{
	if (increase)
	{
		if (this->movementSound->getVolume() != this->movementVolumeMax)
		{
			this->movementSound->setVolume(this->movementVolumeMax);
		}
	}
	else
	{
		if (this->movementSound->getVolume() != this->movementVolumeMin)
		{
			this->movementSound->setVolume(this->movementVolumeMax);
		}
	}
}

void PlayerSoundBox::pauseMovementSound()
{
	this->movementSound->pause();
}

void PlayerSoundBox::unpauseMovementSound()
{
	if (this->movementSound->getStatus() == sf::Sound::Paused)
	{
		this->movementSound->play();
	}
}
