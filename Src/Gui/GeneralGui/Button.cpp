#include <stdafx.h>
#include <Gui/GeneralGui/Gui.h>

//============================//
//Button======================//
//============================//

// Constructor
GUI::Button::Button(
	const float& x, const float& y,
	const float& width, const float& height,
	sf::Font* font, const std::string& text,
	const unsigned& charcter_size,
	const sf::Color& text_idle_color,
	const sf::Color& text_hover_color,
	const sf::Color& text_active_color,
	const sf::Color& idleColor,
	const sf::Color& hoverColor,
	const sf::Color& activeColor,
	const sf::Color& outlineIdleColor,
	const sf::Color& outlineHoverColor,
	const sf::Color& outlineActiveColor,
	short unsigned id) noexcept
	:
	textIdleColor(text_idle_color), textHoverColor(text_hover_color), texActiveColor(text_active_color), id(id),
	outlineActiveColor(outlineActiveColor), outlineHoverColor(outlineHoverColor), outlineIdleColor(outlineIdleColor),
	idleColor(idleColor), activeColor(activeColor), hoverColor(hoverColor),
	font(font),
	buttonState(BTN_IDLE)
{
	//Button shape
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(this->outlineIdleColor);

	//Button text
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->textIdleColor);
	this->text.setCharacterSize(charcter_size);
	this->text.setPosition(this->shape.getPosition().x + 20, this->shape.getPosition().y + 8);
}

GUI::Button::Button(const GUI::Button& other) noexcept
{
	this->activeColor = other.activeColor;
	this->buttonState = other.buttonState;
	this->font = other.font;
	this->hoverColor = other.hoverColor;
	this->id = other.id;
	this->idleColor = other.idleColor;
	this->outlineActiveColor = other.outlineActiveColor;
	this->outlineHoverColor = other.outlineHoverColor;
	this->idleColor = other.outlineIdleColor;
	this->shape = other.shape;
	this->texActiveColor = other.texActiveColor;
	this->text = other.text;
	this->textHoverColor = other.textHoverColor;
	this->textIdleColor = other.textIdleColor;
}

GUI::Button::Button(GUI::Button&& other) noexcept
{
	this->activeColor = std::move(other.activeColor);
	this->buttonState = std::move(other.buttonState);
	this->font = other.font;
	this->hoverColor = std::move(other.hoverColor);
	this->id = other.id;
	this->idleColor = std::move(other.idleColor);
	this->outlineActiveColor = std::move(other.outlineActiveColor);
	this->outlineHoverColor = std::move(other.outlineHoverColor);
	this->idleColor = std::move(other.outlineIdleColor);
	this->shape = std::move(other.shape);
	this->texActiveColor = std::move(other.texActiveColor);
	this->text = std::move(other.text);
	this->textHoverColor = std::move(other.textHoverColor);
	this->textIdleColor = std::move(other.textIdleColor);
}

GUI::Button& GUI::Button::operator= (const GUI::Button& other) noexcept
{
	if (this != &other)
	{
		this->activeColor = other.activeColor;
		this->buttonState = other.buttonState;
		this->font = other.font;
		this->hoverColor = other.hoverColor;
		this->id = other.id;
		this->idleColor = other.idleColor;
		this->outlineActiveColor = other.outlineActiveColor;
		this->outlineHoverColor = other.outlineHoverColor;
		this->idleColor = other.outlineIdleColor;
		this->shape = other.shape;
		this->texActiveColor = other.texActiveColor;
		this->text = other.text;
		this->textHoverColor = other.textHoverColor;
		this->textIdleColor = other.textIdleColor;
	}
	return *this;
}

GUI::Button& GUI::Button::operator=(GUI::Button&& other) noexcept
{
	if (this != &other)
	{
		this->activeColor = std::move(other.activeColor);
		this->buttonState = std::move(other.buttonState);
		this->font = other.font;
		this->hoverColor = std::move(other.hoverColor);
		this->id = other.id;
		this->idleColor = std::move(other.idleColor);
		this->outlineActiveColor = std::move(other.outlineActiveColor);
		this->outlineHoverColor = std::move(other.outlineHoverColor);
		this->idleColor = std::move(other.outlineIdleColor);
		this->shape = std::move(other.shape);
		this->texActiveColor = std::move(other.texActiveColor);
		this->text = std::move(other.text);
		this->textHoverColor = std::move(other.textHoverColor);
		this->textIdleColor = std::move(other.textIdleColor);
	}
	return *this;
}

GUI::Button::~Button()
{
}

//Accessors
const short unsigned& GUI::Button::getId() const
{
	return this->id;
}

const bool GUI::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	else
		return false;
}

const sf::Vector2f GUI::Button::getPosition() const
{
	return this->shape.getPosition();
}

std::string GUI::Button::getText()
{
	return this->text.getString();
}

sf::FloatRect GUI::Button::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

sf::Text& GUI::Button::getSfText()
{
	return this->text;
}

//Seters
void GUI::Button::setPosition(const float& x, const float& y)
{
	this->shape.setPosition(x, y);

	this->text.setPosition(this->shape.getPosition().x + 20, this->shape.getPosition().y + 8);
}

void GUI::Button::setPosition(const sf::Vector2f& position)
{
	this->shape.setPosition(position);

	this->text.setPosition(this->shape.getPosition().x + 20, this->shape.getPosition().y + 8);
}

void GUI::Button::setText(std::string text)
{
	this->text.setString(text);
}

void GUI::Button::setId(const short unsigned& id)
{
	this->id = id;
}

//Functions
void GUI::Button::update(const sf::Vector2i& mousePosition)
{
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
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
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->text.setFillColor(this->textHoverColor);
		this->shape.setFillColor(this->hoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->text.setFillColor(this->texActiveColor);
		this->shape.setFillColor(this->activeColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
