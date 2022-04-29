#include "stdafx.h"
#include "Gui.h"

////========================Button==========================//

// init funcs
GUI::Button::Button(float x, float y, float width, float height, 
	sf::Font* font, const std::string& text, unsigned charcter_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, 
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor, short unsigned id)

	: textIdleColor(text_idle_color), textHoverColor(text_hover_color), texActiveColor(text_active_color), id(id),
	outlineActiveColor(outlineActiveColor), outlineHoverColor(outlineHoverColor), outlineIdleColor(outlineIdleColor),
	idleColor(idleColor), activeColor(activeColor), hoverColor(hoverColor), font(font), buttonState(BTN_IDLE)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(this->outlineIdleColor);

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

const std::string GUI::Button::getText() const
{
	return this->text.getString();
}

//Seters
void GUI::Button::setText(const std::string& text)
{
	this->text.setString(text);
}

void GUI::Button::setId(const short unsigned& id)
{
	this->id = id;
}

//functions

// update bolleans for hoverand pressed
void GUI::Button::update(const sf::Vector2f& mousePosition)
{
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



//========================DropDownBox==========================//

GUI::DropDownList::DropDownList(const float& x, const float& y, const float& width, const float& hight, 
	sf::Font& font, std::string text_list[], const unsigned& number_of_elements,const unsigned& default_index)
	:font(font), showDropBox(false), keyTimeMax(2.f), keyTime(0.f)
{
	this->activeBox = new GUI::Button(x, y + 20, width + 8, hight,
		&this->font, text_list[default_index], 28,
		sf::Color(255, 255, 255, 160), sf::Color(252, 252, 252, 200), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 50)
	);

	this->dropBox.reserve(number_of_elements);

	for (size_t i = 0; i < number_of_elements; ++i)
	{
		this->dropBox.push_back(new GUI::Button(x, y + ((i+1) * hight) + 20, width + 8, hight,
			&this->font, text_list[i], 28,
			sf::Color(255, 255, 255, 150), sf::Color(252, 252, 252, 252), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
			sf::Color(255, 255, 255, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0), i
		));
	}
	
}

GUI::DropDownList::~DropDownList()
{
	for (size_t i = 0; i < this->dropBox.size(); ++i)
	{
		delete this->dropBox[i];
	}

	delete this->activeBox;
}


//Accessors
const unsigned short& GUI::DropDownList::getActiveBoxId() const
{
	return this->activeBox->getId();
}

const bool& GUI::DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

//Functions

void GUI::DropDownList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.f * dt;
	}
}

void GUI::DropDownList::update(const sf::Vector2f& mousePosition, const float& dt)
{
	this->updateKeyTime(dt);

	this->activeBox->update(mousePosition);

	//Show or hide dropdownlist
	if (this->activeBox->isPressed() && this->getKeyTime())
	{ 
		showDropBox = !showDropBox;
	}

	//update droplist
	if (showDropBox)
	{
		for (auto& el : this->dropBox)
		{
			el->update(mousePosition);

			if (el->isPressed() && this->getKeyTime())
			{
				this->showDropBox = false;
				
				this->activeBox->setText(el->getText());
				this->activeBox->setId(el->getId());
			}
		}
	}
}

void GUI::DropDownList::render(sf::RenderTarget& target)
{
	this->activeBox->render(target);

	if (showDropBox)
	{
		for (auto& el : this->dropBox)
		{
			el->render(target);
		}
	}
}
