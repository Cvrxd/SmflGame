#include <stdafx.h>
#include "ISoundsPlayer.h"

template<typename KeyType>
ISoundsPlayer<KeyType>::ISoundsPlayer(SoundsMap& sounds, const float& volume, const float& volumeMax, const float& volumeModifier)
	:sounds(sounds), volume(volume), volumeMax(volumeMax), volumeModifier(volumeModifier)
{
	this->setVolume(volume);
}

template<typename KeyType>
ISoundsPlayer<KeyType>::~ISoundsPlayer()
{
}

template<typename KeyType>
void ISoundsPlayer<KeyType>::stopSounds()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() != sf::Sound::Stopped)
		{
			el.second.second.stop();
		}
	}
}

template<typename KeyType>
void ISoundsPlayer<KeyType>::playSounds()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() != sf::Sound::Playing)
		{
			el.second.second.play();
		}
	}
}

template<typename KeyType>
void ISoundsPlayer<KeyType>::pauseSounds()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() != sf::Sound::Paused)
		{
			el.second.second.pause();
		}
	}
}

template<typename KeyType>
void ISoundsPlayer<KeyType>::increaseVolume()
{
	this->volume += this->volumeModifier;

	if (this->volume > this->volumeMAX)
	{
		this->volume = this->volumeMAX;
	}

	this->setVolume(this->volume);
}

template<typename KeyType>
void ISoundsPlayer<KeyType>::decreaseVolume()
{
	this->volume -= this->volumeModifier;

	if (this->volume < 0)
	{
		this->volume = 0;
	}

	this->setVolume(this->volume);
}

template<typename KeyType>
void ISoundsPlayer<KeyType>::setVolume(const float& volume)
{
	for (auto& el : this->sounds)
	{
		el.second.seconsd.setVolume(volume);
	}
}

template<typename KeyType>
const float& ISoundsPlayer<KeyType>::getVolume() const
{
	return this->volume;
}

template<typename KeyType>
const float& ISoundsPlayer<KeyType>::getMaxVolume() const
{
	return this->volumeMax;
}

