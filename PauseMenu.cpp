#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->background.setSize(static_cast<sf::Vector2f>(window.getSize()));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(background.getSize().x / 4.f, background.getSize().y - 100.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(window.getSize().x / 2.f - this->container.getSize().x / 2.f, 30.f);

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(220,220,220,250));
	this->menuText.setCharacterSize(70);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(this->container.getPosition().x + 140.f, this->container.getPosition().y + 100);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Accessors
std::unordered_map<std::string, GUI::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Functions

const bool PauseMenu::isButtonPressed(const std::string& key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string& key, const float& y, const float& modifier_x, const std::string& text)
{
	float width = 230.f;
	float hight = 70.f;
	float x = (this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f) + modifier_x;

	this->buttons[key] = new GUI::Button(x, y, width, hight,
		&this->font, text, 60,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void PauseMenu::update(const sf::Vector2i& mousePosition)
{
	for (auto& el : this->buttons)
	{
		el.second->update(mousePosition);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->menuText);

	for (auto& el : buttons)
	{
		el.second->render(target);
	}
}

