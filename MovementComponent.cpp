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

const bool MovementComponent::idle() const
{
	return this->velocity.x == 0.f && this->velocity.y == 0.f;
}

//Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Accelerating sprite untill it reaches his max velocity

	this->velocity.x += this->acceleration * dir_x;
	
	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	//Decelerate the sprite and controls the max velocity
	//Moves the sprite
	if (this->velocity.x > 0.f) //check for positive x
	{
		// Max velocity check x
		if (this->velocity.x > this->maxVelocity)
		{
			this->velocity.x = this->maxVelocity;
		}

		//Deceleration x
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0;
		}
	}
	else if (this->velocity.x < 0.f) // check for negative x
	{
		//Max velocity check x
		if (this->velocity.x < -this->maxVelocity)
		{
			this->velocity.x = -this->maxVelocity;
		}

		//Deceleration x
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0;
		}
	}

	if (this->velocity.y > 0.f) //check for positive y
	{
		// Max velocity check y
		if (this->velocity.y > this->maxVelocity)
		{
			this->velocity.y = this->maxVelocity;
		}

		//Deceleration y
		this->velocity.y -= this->deceleration;
		if (this->velocity.y < 0.f)
		{
			this->velocity.y = 0;
		}
	}
	else if (this->velocity.y < 0.f) // check for negative y
	{
		//Max velocity check y
		if (this->velocity.y < -this->maxVelocity)
		{
			this->velocity.y = -this->maxVelocity;
		}

		//Deceleration y
		this->velocity.y += this->deceleration;
		if (this->velocity.y > 0.f)
		{
			this->velocity.y = 0;
		}
	}

	//Final move
	this->sprite.move(this->velocity * dt);  //Uses velocity
}
