#pragma once
#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class AnimationComponent
{
private:
	// core variables

	//////////////////
	class Animation
	{
	public:
		//Variables core
		sf::Texture& textureSheet;
		sf::Sprite& sprite;

		float animationTimer;
		float timer;
		int width;
		int height;
		bool done;

		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		//Constructor
		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, 
			const int& start_frame_x, const int& start_frame_y, 
			const int& frame_x, const int& frame_y,
			const int& width, const int& height, const float& animationTimer)
			:sprite(sprite), textureSheet(textureSheet), width(width), height(height), animationTimer(animationTimer)
		{
			this->timer = 0.f;

			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frame_x * width, frame_y * height, width, height);

			this->sprite.setTexture(this->textureSheet);
			this->sprite.setTextureRect(this->startRect);
		}

		//Functions

		const bool& isDone()
		{
			return this->done;
		}

		//Play animation without modifier
		const bool& play(const float& dt)
		{
			this->done = false;

			//Update timer
			this->timer += 100.f * dt;

			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				if (this->currentRect != this->endRect)//Animate
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}
			}
			this->sprite.setTextureRect(this->currentRect);
			
			return this->done;
		}

		//Play animation with modifiers
		const bool& play(const float& dt, float percentage)
		{
			if (percentage < 0.5f)
			{
				percentage = 0.5f;
			}

			this->done = false;

			//Update timer
			this->timer += percentage * 100.f * dt;

			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				if (this->currentRect != this->endRect)//Animate
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}
			}
			this->sprite.setTextureRect(this->currentRect);

			return this->done;
		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};
	//////////////////

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	//Functions
	const bool& isDone(const std::string& key);

	void addAnimation(const std::string key,
		const int& start_frame_x, const int& start_frame_y,
		const int& frame_x, const int& frame_y,
		const int& width, const int& height, const float& animationTimer); // -__-

	const bool& play(const std::string& key, const float& dt, const bool priority = false);
	const bool& play(const std::string& key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};
