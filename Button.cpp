#include "Button.h"

// init funcs
Button::Button(float x, float y, float width, float height, 
	sf::Font* font, const std::string& text, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(25);
	this->text.setPosition(this->shape.getPosition().x + 20, this->shape.getPosition().y + 8);

	this->idleColor = idleColor;
	this->activeColor = activeColor;
	this->hoverColor = hoverColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

//Accessors

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	else
		return false;
}

//functions

void Button::update(const sf::Vector2f& mousePosition)
{
	// update bolleans for hover and pressed

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->buttonState = BTN_HOVER;

		//Active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
