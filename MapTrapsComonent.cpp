#include "stdafx.h"
#include "MapTrapsComonent.h"

//=======================
//Trap===================
//=======================

//Init functions
inline void MapTrapsComonent::Trap::initAnimations(sf::Texture& texture)
{
	this->animationComponent = { &this->sprite, &texture };

	switch (this->type)
	{
	case TrapType::BEAR_TRAP:

		this->sprite.setScale(3.f, 3.f);
		this->animationComponent.addAnimation("PLAY", 0, 0, 3, 0, 32, 32, 10.f);

		break;
	case TrapType::FIRE_TRAP:

		this->sprite.setScale(3.f, 3.f);
		this->animationComponent.addAnimation("PLAY", 0, 0, 13, 0, 32, 41, 7.f);

		break;
	case TrapType::SPIKE_TRAP:

		this->sprite.setScale(3.f, 3.f);
		this->animationComponent.addAnimation("PLAY", 0, 0, 13, 0, 32, 32, 7.f);

		break;
	default:
		break;
	}
}

//Constructors
MapTrapsComonent::Trap::Trap(const sf::Vector2f& position, const TrapType& type, sf::Texture& texture, const int& damage) noexcept
	:damage(damage), type(type)
{
	//this->sprite.setTexture(texture);
	this->sprite.setPosition(position);
	this->initAnimations(texture);
}

MapTrapsComonent::Trap::Trap(Trap&& other) noexcept
	:damage(other.damage), sprite(std::move(other.sprite)), type(other.type)
{
	this->animationComponent = std::move(other.animationComponent);
}

MapTrapsComonent::Trap::~Trap()
{
}

//Operators
MapTrapsComonent::Trap& MapTrapsComonent::Trap::operator=(Trap&& other) noexcept
{
	if (this != &other)
	{
		this->damage = other.damage;
		this->type = other.type;
		this->sprite = std::move(other.sprite);
		this->animationComponent = std::move(other.animationComponent);

	}
	return *this;
}

//Accessors
const int& MapTrapsComonent::Trap::getDamage() const
{
	return this->damage;
}

//Public functions
bool MapTrapsComonent::Trap::updateAnimation(const float& dt)
{
	if (this->animationComponent.play("PLAY", dt, true))
	{
		return true;
	}
	else
	{
		return false;
	}
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

//Constructor
MapTrapsComonent::MapTrapsComonent(Player& player, const int& gameDifficulty, const int& trapsCount)
	:trapsCount(trapsCount), gameDifficulty(gameDifficulty), player(player)
{
	this->initTextures  ();
	this->traps.reserve (trapsCount);
}

MapTrapsComonent::~MapTrapsComonent()
{
}

//Public funtions
void MapTrapsComonent::addTrap(const float& x, const float& y, const TrapType& trap_type)
{
	this->traps.push_back(std::move(Trap(sf::Vector2f(x, y), trap_type, this->trapsTextures[trap_type], this->gameDifficulty)));
}

void MapTrapsComonent::update(const float& dt)
{
	for (auto& el : this->traps)
	{
		if (el.updateAnimation(dt))
		{
			if (el.update(dt, this->player.getGlobalBounds()))
			{
				this->player.loseHP(el.getDamage());
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
