#include "stdafx.h"
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
	this->texts[text].setFont(this->font);
	this->texts[text].setCharacterSize(characterSize);
	this->texts[text].setString(text);
	this->texts[text].setFillColor(color);
}

void PopUpTextComponent::popUpText(sf::RenderTarget& target, const std::string& key, const sf::Vector2f position)
{
	this->texts[key].setPosition(position.x - this->offsetX, position.y - this->offsetY - ++this->modifierY);

	target.draw(this->texts[key]);
}

void PopUpTextComponent::prepareText(const std::string& key)
{
	this->offsetX = static_cast<float> (std::rand() % 50);
	this->offsetY = static_cast<float> (std::rand() % 50);

	this->orirginalTextColor = this->texts[key].getFillColor();
}

void PopUpTextComponent::resetText(const std::string& key)
{
	this->texts[key].setFillColor(this->orirginalTextColor);

	this->modifierY = this->offsetY;
}
