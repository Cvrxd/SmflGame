#include <stdafx.h>
#include "PauseMenu.h"

//Initialisation
inline void PauseMenu::initSounds()
{
	this->clickSound.first.loadFromFile("Sounds/game_state/skills_menu_sounds/click.wav");
	this->clickSound.second.setBuffer(this->clickSound.first);
	this->clickSound.second.setVolume(10.f);
}

//Constructor
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) noexcept
	: font(font)
{
	//Background
	this->background.setSize(static_cast<sf::Vector2f>(window.getSize()));
	this->background.setFillColor(sf::Color(10, 10, 10, 100));

	//Container for buttons
	this->container.setSize(sf::Vector2f(background.getSize().x / 4.f, background.getSize().y - 100.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(window.getSize().x / 2.f - this->container.getSize().x / 2.f, 30.f);

	//Text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(220,220,220,250));
	this->menuText.setCharacterSize(70);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(this->container.getPosition().x + 140.f, this->container.getPosition().y + 100);

	//Sounds
	this->initSounds();
}

PauseMenu::~PauseMenu()
{
}

//Accessors
std::unordered_map<std::string, std::unique_ptr<GUI::Button>>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Functions
void PauseMenu::playClickSound()
{
	this->clickSound.second.play();
}

const bool PauseMenu::isButtonPressed(const std::string& key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string& key, const float& y, const float& modifier_x, const std::string& text)
{
	float width  = 230.f;
	float hight  = 70.f;
	float x      = (this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f) + modifier_x;

	this->buttons[key] = std::make_unique<GUI::Button>(x, y, width, hight, &this->font, text, 60);
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

