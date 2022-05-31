#include "stdafx.h"
#include "PopUpTextComponent.h"

//Private funtions
void PopUpTextComponent::updateText(const std::string& key)
{
	//
}

//Constructor
PopUpTextComponent::PopUpTextComponent(sf::Font& font) noexcept
	:font(font)
{
	
}

PopUpTextComponent::~PopUpTextComponent()
{
}

//Functions
void PopUpTextComponent::addText(const std::string& text, const sf::Color& color, const unsigned int& characterSize)
{
	this->texts[text].setFont(this->font);
	this->texts[text].setCharacterSize(characterSize);
	this->texts[text].setString(text);
	this->texts[text].setFillColor(color);
}

bool PopUpTextComponent::showText(sf::RenderTarget& target, const std::string& key, const sf::Vector2f position)
{
	this->updateText(key);

	//
	
	return true;
}
