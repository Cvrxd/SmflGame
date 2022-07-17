#include <stdafx.h>
#include "Entity.h"

//Initialisation functions
void Entity::initVariables()
{
}

//Constructor
Entity::Entity() noexcept
{
	this->initVariables();
}

Entity::~Entity()
{
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const float& offset_x, const float& offset_y, const float& width, const float& height)
{
	this->hitboxComponent = { this->sprite, offset_x, offset_y, width, height };
}

void Entity::createMovementComponent(const float& maxVelocity, const float& acceleration, const float& deceleration)
{
	this->movementComponent = { this->sprite, maxVelocity, acceleration, deceleration };
}


//Accessors
const sf::Vector2f& Entity::getPosition() const
{
	return this->hitboxComponent.getPositionHitbox();
}

const sf::Vector2f Entity::getCenter() const
{
	return this->hitboxComponent.getPositionHitbox() + 
		sf::Vector2f(this->hitboxComponent.getGlobalBounds().width / 2.f, this->hitboxComponent.getGlobalBounds().height / 2.f);
}

const sf::Vector2i Entity::getGridPosition(const int& gridSizeI) const
{
	return sf::Vector2i(static_cast<int>(this->hitboxComponent.getPositionHitbox().x) / gridSizeI,
		static_cast<int>(this->hitboxComponent.getPositionHitbox().y) / gridSizeI);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	return this->hitboxComponent.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPosition(const float& dt)
{
	return this->hitboxComponent.getNextPosition(this->movementComponent.getVelocity() * dt);
}

// Functions
void Entity::stopVelocity()
{

	this->movementComponent.stopVelocity();
}

void Entity::stopVelocityX()
{
	this->movementComponent.stopVelocityX();
}

void Entity::stopVelocityY()
{
	this->movementComponent.stopVelocityY();

}

void Entity::setPosition(const float& x, const float& y)
{
	this->hitboxComponent.setPosition(x, y);
}	

void Entity::move(const float& dir_x, const float& dir_y, const float& dt, const bool& dash)
{
	this->movementComponent.move(dir_x, dir_y, dt, dash);
}
