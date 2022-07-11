#include "stdafx.h"
#include "AnimationComponent.h"

//Constructors
AnimationComponent::AnimationComponent(sf::Sprite* sprite, sf::Texture* textureSheet) noexcept
	:sprite(sprite), 
	textureSheet(textureSheet), 
	lastAnimation(nullptr), 
	priorityAnimation(nullptr)
{

}

AnimationComponent::AnimationComponent(const AnimationComponent& other) noexcept
	:sprite(other.sprite), textureSheet(other.textureSheet)
{
	this->animations        = other.animations;
	this->priorityAnimation = other.priorityAnimation;
	this->lastAnimation     = other.lastAnimation;
}

AnimationComponent& AnimationComponent::operator=(AnimationComponent&& other) noexcept
{
	if (this != &other)
	{
		this->textureSheet      = std::move(other.textureSheet);
		this->sprite            = std::move(other.sprite);
		this->animations        = std::move(other.animations);
		this->priorityAnimation = std::move(other.priorityAnimation);
		this->lastAnimation     = std::move(other.lastAnimation);
	}
	return *this;
}

AnimationComponent& AnimationComponent::operator=(const AnimationComponent& other) noexcept
{
	if (this != &other)
	{
		this->textureSheet      = other.textureSheet;
		this->sprite            = other.sprite;
		this->animations        = other.animations;
		this->priorityAnimation = other.priorityAnimation;
		this->lastAnimation     = other.lastAnimation;
	}
	return *this;
}

AnimationComponent::~AnimationComponent()
{
}

//Functions
const bool& AnimationComponent::isDone(const std::string& key)
{
	return this->animations[key]->isDone();
}

void AnimationComponent::addAnimation(const std::string key,
	const int& start_frame_x, const int& start_frame_y,
	const int& frame_x,       const int& frame_y,
	const int& width,         const int& height, 
	const float& animationTimer)
{
	this->animations[key] = std::make_shared<Animation>(
		this->sprite,  this->textureSheet, 
		start_frame_x, start_frame_y, 
		frame_x,       start_frame_y, 
		width,         height, 
		animationTimer);

}

const bool& AnimationComponent::play(const std::string& key, const float& dt, const bool priority)
{
	if (this->priorityAnimation) //If there is a prioritu animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			//If prioty animation is done, remove it 
			if(this->animations[key]->play(dt))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else //If there is no priority animation 
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt);
	}
	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string& key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation) //If there is a prioritu animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			 
			//If prioty animation is done, remove it 
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else //If there is no priority animation 
	{
		//Set priority
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}
	return this->animations[key]->isDone();
}
