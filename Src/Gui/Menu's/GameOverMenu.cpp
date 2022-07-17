#include <stdafx.h>
#include "GameOverMenu.h"

//Init fucntions
inline void GameOverMenu::initGui() noexcept
{
	//Bacground
	this->background.setSize      (static_cast<sf::Vector2f>(window.getSize()));
	this->background.setFillColor (sf::Color(10, 10, 10, 150));

	//Container
	this->container.setSize       (sf::Vector2f(this->background.getSize().x / 4.f, this->background.getSize().y - 100.f));
	this->container.setFillColor  (sf::Color(20, 20, 20, 200));
	this->container.setPosition   (this->window.getSize().x / 2.f - this->container.getSize().x / 2.f, 30.f);

	//Text
	this->text.setString        ("GAME OVER");
	this->text.setFont          (this->font);
	this->text.setCharacterSize (70);
	this->text.setFillColor     (sf::Color::White);
	this->text.setPosition      (this->container.getPosition().x + 80.f, this->container.getPosition().y + 100);

	//Exit button
	this->exitButton = std::make_unique<GUI::Button>(this->text.getPosition().x + 70.f, this->text.getPosition().y + 650.f,
		150, 70, &this->font, "Exit", 60);
}

//Constructor
GameOverMenu::GameOverMenu(sf::RenderWindow& window, sf::Font& font) noexcept
	:window(window), font(font)
{
	this->initGui();
}

GameOverMenu::~GameOverMenu()
{
}

//Accessors
const bool GameOverMenu::exitButtonIsPressed() const
{
	return this->exitButton->isPressed();
}

//Public functions
void GameOverMenu::update(const float& dt, sf::Vector2i& mousePosWindow)
{
	//Exit button update
	this->exitButton->update(mousePosWindow);
}

void GameOverMenu::render(sf::RenderTarget& target)
{
	//Background shapes render
	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->text);

	//Button render
	this->exitButton->render(target);
}
