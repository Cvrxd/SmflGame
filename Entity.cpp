#include "stdafx.h"
#include "Entity.h"

//Initialisation functions
void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->hitboxComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const float& offset_x, const float& offset_y, const float& width, const float& height)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float& maxVelocity, const float& acceleration, const float& deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}


//Accessors
const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getPositionHitbox();
	}
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPositionHitbox() +
		sf::Vector2f(
			this->hitboxComponent->getGlobalBounds().width / 2.f,
			this->hitboxComponent->getGlobalBounds().height / 2.f);

	return this->sprite.getPosition() + 
		sf::Vector2f(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f);
}

const sf::Vector2i Entity::getGridPosition(const int& gridSizeI) const
{
	if (this->hitboxComponent)
	{
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPositionHitbox().x) / gridSizeI, 
			static_cast<int>(this->hitboxComponent->getPositionHitbox().y) / gridSizeI);
	}
	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPosition(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}
	return sf::FloatRect();
}

// Functions
void Entity::stopVelocity()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocity();
	}
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocityX();
	}
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocityY();
	}
}

void Entity::setPosition(const float& x, const float& y)
{
	if (this->hitboxComponent)
	{
		this->hitboxComponent->setPosition(x, y);
	}
	else
	{
		this->sprite.setPosition(x, y);
	}
}	

void Entity::move(const float& dir_x, const float& dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);
	} 
	else
	{
		//
	}
}
