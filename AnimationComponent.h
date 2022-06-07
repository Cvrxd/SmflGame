#pragma once
//#include"stdafx.h"

class AnimationComponent
{
private:
	//////////////////
	class Animation
	{
	public:
		//Variables core
		sf::Texture*  textureSheet;
		sf::Sprite*   sprite;

		bool    done;
		int     width;
		int     height;
		float   animationTimer;
		float   timer;

		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		//Constructor
		Animation() {};

		Animation(sf::Sprite* sprite, sf::Texture* textureSheet,
			const int& start_frame_x, const int& start_frame_y,
			const int& frame_x, const int& frame_y,
			const int& width, const int& height, const float& animationTimer) noexcept
			:sprite(sprite), textureSheet(textureSheet), width(width), height(height), animationTimer(animationTimer)
		{
			this->timer = 0.f;
			this->done = false;

			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frame_x * width, frame_y * height, width, height);

			this->sprite->setTexture(*this->textureSheet);
			this->sprite->setTextureRect(this->startRect);
		}

		Animation& operator= (const Animation& other)
		{
			this->animationTimer = other.animationTimer;
			this->currentRect = other.currentRect;
			this->done = other.done;
			this->endRect = other.endRect;
			this->height = other.height;
			this->sprite = other.sprite;
			this->textureSheet = other.textureSheet;
			this->timer = other.timer;
			this->width = other.width;

			return *this;
		}

		//Functions
		const bool& isDone()
		{
			return this->done;
		}

		//Play animation without modifier
		inline const bool& play(const float& dt)
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
			this->sprite->setTextureRect(this->currentRect);

			return this->done;
		}

		//Play animation with modifiers
		inline const bool& play(const float& dt, float percentage)
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
			this->sprite->setTextureRect(this->currentRect);

			return this->done;
		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};
	//////////////////

	using MapAnimations = std::unordered_map<std::string, std::shared_ptr<Animation>>;
	using AnimationSptr = std::shared_ptr<Animation>;

	//Variables
	sf::Sprite*     sprite;
	sf::Texture*    textureSheet;

	AnimationSptr   lastAnimation;
	AnimationSptr   priorityAnimation;

	MapAnimations   animations;

public:
	AnimationComponent() {};
	AnimationComponent(sf::Sprite* sprite, sf::Texture* textureSheet)   noexcept;
	AnimationComponent(const AnimationComponent& other)                 noexcept;

	AnimationComponent& operator=(AnimationComponent&& other)           noexcept;
	AnimationComponent& operator=(const AnimationComponent& other)      noexcept;

	virtual ~AnimationComponent();

	//Functions
	const bool& isDone(const std::string& key);

	void addAnimation(const std::string key,
		const int& start_frame_x, const int& start_frame_y,
		const int& frame_x, const int& frame_y,
		const int& width, const int& height, const float& animationTimer); 

	const bool& play(const std::string& key, const float& dt, const bool priority = false);
	const bool& play(const std::string& key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

