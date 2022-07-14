#include "stdafx.h"
#include "MapTrapsComonent.h"


//=======================
//Trap===================
//=======================

//Init functions
inline void MapTrapsComonent::Trap::initAnimations()
{
	switch (this->type)
	{
	case TrapType::BEAR_TRAP:

		this->sprite.setScale(3.f, 3.f);
		this->animationComponent.addAnimation("PLAY", 0, 0, 3, 0, 32, 32, 15.f);

		break;
	case TrapType::FIRE_TRAP:

		this->sprite.setScale(3.f, 3.f);
		this->animationComponent.addAnimation("PLAY", 0, 0, 13, 0, 32, 41, 10.f);

		break;
	case TrapType::SPIKE_TRAP:

		this->sprite.setScale(3.f, 3.f);
		this->animationComponent.addAnimation("PLAY", 0, 0, 13, 0, 32, 32, 10.f);

		break;
	default:
		break;
	}
}

//Constructors
MapTrapsComonent::Trap::Trap(const sf::Vector2f& position, const TrapType& type, sf::Texture& texture, const int& damage) noexcept
	:texture(texture), 
	damage(damage), 
	type(type), 
	animationComponent(&this->sprite, &this->texture)
{
	this->sprite.setPosition (position);
	this->initAnimations     ();
}

MapTrapsComonent::Trap::~Trap()
{
}

//Accessors
const int& MapTrapsComonent::Trap::getDamage() const
{
	return this->damage;
}

const TrapType& MapTrapsComonent::Trap::getType() const
{
	return this->type;
}

//Public functions
bool MapTrapsComonent::Trap::updateAnimation(const float& dt)
{
	this->animationComponent.play("PLAY", dt);

	return this->animationComponent.isDone("PLAY");
}

bool MapTrapsComonent::Trap::update(const float& dt, const sf::FloatRect& playerBounds)
{
	if (this->sprite.getGlobalBounds().intersects(playerBounds))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MapTrapsComonent::Trap::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

//=======================
//Map traps component====
//=======================

//Init functions
inline void MapTrapsComonent::initTextures()
{
	if (!this->trapsTextures[TrapType::FIRE_TRAP].loadFromFile("Textures/tiles/traps/fire_trap.png"))
	{
		throw("UNABLE TO OPEN fire_trap.png");
	}
	if (!this->trapsTextures[TrapType::BEAR_TRAP].loadFromFile("Textures/tiles/traps/bear_trap.png"))
	{
		throw("UNABLE TO OPEN bear_trap.png");
	}
	if (!this->trapsTextures[TrapType::SPIKE_TRAP].loadFromFile("Textures/tiles/traps/spike_trap.png"))
	{
		throw("UNABLE TO OPEN spike_trap.png");
	}
}

inline void MapTrapsComonent::initSounds()
{
	//Loading soundBuffers
	if (!this->sounds[TrapType::FIRE_TRAP].first.loadFromFile("Sounds/game_state/traps/fire_trap.wav"))
	{
		throw("UNABLE TO LOAD fire_trap.wav");
	}
	if (!this->sounds[TrapType::SPIKE_TRAP].first.loadFromFile("Sounds/game_state/traps/spike_trap.wav"))
	{
		throw("UNABLE TO LOAD spike_trap.wav");
	}

	//Volume and sound
	for (auto& el : this->sounds)
	{
		el.second.second.setBuffer(el.second.first);
		el.second.second.setVolume(this->trapVolume);
	}
}

//Sound functions
inline void MapTrapsComonent::playTrapSound(const TrapType& sound)
{
	if (this->sounds[sound].second.getStatus() != sf::Sound::Playing)
	{
		this->sounds[sound].second.play();
	}
}

//Constructor
MapTrapsComonent::MapTrapsComonent(Player& player, const unsigned int& gameDifficulty, const unsigned int& trapsCount)
	:trapsCount(trapsCount), 
	gameDifficulty(gameDifficulty), 
	player(player),
	trapVolume(2.f)
{
	this->traps.reserve (trapsCount);
	this->initTextures  ();
	this->initSounds    ();
}

MapTrapsComonent::~MapTrapsComonent()
{
	this->stopSounds();
}

//Sounds functions
void MapTrapsComonent::stopSounds()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() != sf::Sound::Stopped)
		{
			el.second.second.stop();
		}
	}
}

void MapTrapsComonent::playSounds()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() != sf::Sound::Paused)
		{
			el.second.second.play();
		}
	}
}

void MapTrapsComonent::pauseSounds()
{
	for (auto& el : this->sounds)
	{
		if (el.second.second.getStatus() != sf::Sound::Paused)
		{
			el.second.second.pause();
		}
	}
}

void MapTrapsComonent::increaseSoundsVolume()
{
	for (auto& el : this->sounds)
	{
		el.second.second.setVolume(el.second.second.getVolume() + (this->trapVolume * VOLUME_MODIFIER / 100.f));
	}
}

void MapTrapsComonent::decreaseSoundsVolume()
{
	for (auto& el : this->sounds)
	{
		el.second.second.setVolume(el.second.second.getVolume() - (this->trapVolume * VOLUME_MODIFIER / 100.f));
	}
}

void MapTrapsComonent::setSoundsVolume(const float& volume)
{
	for (auto& el : this->sounds)
	{
		el.second.second.setVolume(volume);
	}
}

//Public funtions
void MapTrapsComonent::addTrap(const float& x, const float& y, const TrapType& trap_type)
{
	this->traps.emplace_back(sf::Vector2f(x, y), trap_type, this->trapsTextures[trap_type], this->gameDifficulty);
}

void MapTrapsComonent::update(const float& dt)
{
	for (auto& el : this->traps)
	{
		if (el.updateAnimation(dt))
		{
			if (el.update(dt, this->player.getGlobalBounds()))
			{
				//Player lose hp
				this->player.loseHP(el.getDamage());

				//Sound
				this->playTrapSound(el.getType());
			}
		}
	}
}

void MapTrapsComonent::render(sf::RenderTarget& target)
{
	for (auto& el : this->traps)
	{
		el.render(target);
	}
}
