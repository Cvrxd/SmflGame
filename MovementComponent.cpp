#include "MovementComponent.h"

//Initialisation
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	:sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	
}

MovementComponent::~MovementComponent()
{
}

//Accessors
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

//Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Accelerating sprite untill it reaches his max velocity

	this->velocity.x += this->acceleration * dir_x;

	if (this->velocity.x > 0.f) //check for right direction
	{
		if (this->velocity.x > this->maxVelocity)
		{
			this->velocity.x = this->maxVelocity;
		}
	}
	else if (this->velocity.x < 0.f) //check for left direction
	{
		if (this->velocity.x < -this->maxVelocity)
		{
			this->velocity.x = -this->maxVelocity;
		}
	}
	
	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	//Deceleration
	if (this->velocity.x > 0.f) //check for right direction
	{
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0;
		}
	}
	else if (this->velocity.x < 0.f)
	{
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0;
		}
	}
	//Final move
	this->sprite.move(this->velocity * dt);  //Uses velocity
}
