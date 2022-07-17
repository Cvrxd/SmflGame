#include "stdafx.h"
#include "IMusicPlayer.h"

template<typename KeyType>
IMusicPlayer<KeyType>::IMusicPlayer(MusicMap& music, const float& volume, const float& volumeMax, const float& volumeModifier)
	:music(music), volume(volume), volumeMax(volumeMax), volumeModifier(volumeModifier)
{
	this->setVolume(volume);
}

template<typename KeyType>
IMusicPlayer<KeyType>::~IMusicPlayer()
{
}

template<typename KeyType>
void IMusicPlayer<KeyType>::stopMusic()
{
	for (auto& el : this->music)
	{
		if (el.second.getStatus() != sf::Music::Stopped)
		{
			el.second.stop();
		}
	}
}

template<typename KeyType>
void IMusicPlayer<KeyType>::playMusic()
{
	for (auto& el : this->music)
	{
		if (el.second.getStatus() != sf::Music::Playing)
		{
			el.second.play();
		}
	}
}

template<typename KeyType>
void IMusicPlayer<KeyType>::pauseMusic()
{
	for (auto& el : this->music)
	{
		if (el.second.getStatus() != sf::Music::Paused)
		{
			el.second.pause();
		}
	}
}

template<typename KeyType>
void IMusicPlayer<KeyType>::increaseVolume()
{
	this->volume += this->volumeModifier;

	if (this->volume > this->volumeMAX)
	{
		this->volume = this->volumeMAX;
	}

	this->setVolume(this->volume);
}

template<typename KeyType>
void IMusicPlayer<KeyType>::decreaseVolume()
{
	this->volume -= this->volumeModifier;

	if (this->volume < 0)
	{
		this->volume = 0;
	}

	this->setVolume(this->volume);
}

template<typename KeyType>
void IMusicPlayer<KeyType>::setVolume(const float& volume)
{
	for (auto& el : this->music)
	{
		el.second.setVolume(volume);
	}
}

template<typename KeyType>
const float& IMusicPlayer<KeyType>::getVolume() const
{
	return this->volume;
}

template<typename KeyType>
const float& IMusicPlayer<KeyType>::getMaxVolume() const
{
	return this->volumeMax;
}


