#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet)
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

void AnimationComponent::addAnimation(const std::string key, 
	const int& start_frame_x, const int& start_frame_y,
	const int& frame_x, const int& frame_y,
	const int& width, const int& height, const float& animationTimer) // -__-
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet, 
		start_frame_x, start_frame_y, frame_x, start_frame_y, 
		width, height, animationTimer);

}

void AnimationComponent::play(const std::string& key, const float& dt)
{
	this->animations[key]->play(dt);
}
