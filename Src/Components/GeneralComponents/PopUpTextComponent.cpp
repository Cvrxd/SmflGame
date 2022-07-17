#include <stdafx.h>
#include "PopUpTextComponent.h"

//Constructor
PopUpTextComponent::PopUpTextComponent(const sf::Font& font) noexcept
	:font(font)
{
	
}

PopUpTextComponent::~PopUpTextComponent()
{
}

//Accessors
const float& PopUpTextComponent::getpTextExpireTime() const
{
	return this->textExpireTime;
}

//Functions
void PopUpTextComponent::addText(const std::string& text, const sf::Color& color, const unsigned int& characterSize)
{
	this->textsMap[text].setFont          (this->font);
	this->textsMap[text].setCharacterSize (characterSize);
	this->textsMap[text].setString        (text);
	this->textsMap[text].setFillColor     (color);
}

void PopUpTextComponent::popUpText(sf::RenderTarget& target, const std::string& key, const sf::Vector2f position)
{
	this->textsMap[key].setPosition(position.x - this->offsetX, position.y - this->offsetY - ++this->modifierY);

	target.draw(this->textsMap[key]);
}

void PopUpTextComponent::prepareText(const std::string& key)
{
	this->offsetX = static_cast<float> (std::rand() % 50) - 10.f;
	this->offsetY = static_cast<float> (std::rand() % 50);

	this->orirginalTextColor = this->textsMap[key].getFillColor();
}

void PopUpTextComponent::resetText(const std::string& key)
{
	this->textsMap[key].setFillColor(this->orirginalTextColor);

	this->modifierY = this->offsetY;

}
