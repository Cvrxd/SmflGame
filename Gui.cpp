#include "Gui.h"

/////////Button//////////

// init funcs
GUI::Button::Button(float x, float y, float width, float height, 
	sf::Font* font, const std::string& text, unsigned charcter_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	:textIdleColor(text_idle_color), textHoverColor(text_hover_color), texActiveColor(text_active_color)
{
	this->idleColor = idleColor;
	this->activeColor = activeColor;
	this->hoverColor = hoverColor;

	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->textIdleColor);
	this->text.setCharacterSize(charcter_size);
	this->text.setPosition(this->shape.getPosition().x + 20, this->shape.getPosition().y + 8);
}

GUI::Button::~Button()
{
}

//Accessors

const bool GUI::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	else
		return false;
}

//functions

void GUI::Button::update(const sf::Vector2f& mousePosition)
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
		this->text.setFillColor(this->textIdleColor);
		this->shape.setFillColor(this->idleColor);
		break;

	case BTN_HOVER:
		this->text.setFillColor(this->textHoverColor);
		this->shape.setFillColor(this->hoverColor);
		break;

	case BTN_ACTIVE:
		this->text.setFillColor(this->texActiveColor);
		this->shape.setFillColor(this->activeColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//////////DropDownBox/////////

GUI::DropDownList::DropDownList(sf::Font& font)
	:font(font)
{
}

GUI::DropDownList::~DropDownList()
{
}

void GUI::DropDownList::update(const sf::Vector2f& mousePosition)
{
}

void GUI::DropDownList::render(sf::RenderTarget& target)
{
}
