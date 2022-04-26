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

		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

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
		void play(const float& dt)
		{
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
				}
			}

			this->sprite.setTextureRect(this->currentRect);
		}
		
		void reset()
		{
			this->timer = 0.f;
			this->currentRect = this->startRect;
		}
	};
	//////////////////

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::map<std::string, Animation*> animations;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string key,
		const int& start_frame_x, const int& start_frame_y,
		const int& frame_x, const int& frame_y,
		const int& width, const int& height, const float& animationTimer); // -__-

	void play(const std::string& key, const float& dt);
};

