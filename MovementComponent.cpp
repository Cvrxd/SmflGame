#include "stdafx.h"
#include "MovementComponent.h"

//Initialisation
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& maxVelocity, const float& acceleration, const float& deceleration)
	:sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	
}

MovementComponent::~MovementComponent()
{
}

//Accessors

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		return this->velocity.x == 0.f && this->velocity.y == 0.f;
		break;
	case MOVING:
		return this->velocity.x != 0.f || this->velocity.y != 0.f;
		break;
	case MOVING_LEFT:
		return this->velocity.x < 0.f;
		break;
	case MOVING_RIGHT:
		return this->velocity.x > 0.f;
		break;
	case MOVE_UP:
		return this->velocity.y < 0.f;
		break;
	case MOVE_DOWN:
		return this->velocity.y > 0.f;
		break;
	default:
		break;
	}
}

//Functions
void MovementComponent::move(const float& dir_x, const float& dir_y, const float& dt)
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
