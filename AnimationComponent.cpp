#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& el : this->animations)
	{
		delete el.second;
	}
}

//Functions

const bool& AnimationComponent::isDone(const std::string& key)
{
	return this->animations[key]->isDone();
}

void AnimationComponent::addAnimation(const std::string key,
	const int& start_frame_x, const int& start_frame_y,
	const int& frame_x, const int& frame_y,
	const int& width, const int& height, const float& animationTimer) // -__-
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet, 
		start_frame_x, start_frame_y, frame_x, start_frame_y, 
		width, height, animationTimer);

}

const bool& AnimationComponent::play(const std::string& key, const float& dt, const bool priority)
{
	if (this->priorityAnimation) //If there is a prioritu animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
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
				this->priorityAnimation = NULL;
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
			if (this->lastAnimation == NULL)
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
	//Change later
	if (this->priorityAnimation) //If there is a prioritu animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
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
				this->priorityAnimation = NULL;
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
			if (this->lastAnimation == NULL)
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
