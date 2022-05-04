#include "stdafx.h"
#include "Gui.h"

////========================Button==========================////

// init funcs
GUI::Button::Button(const float& x, const float& y, const float& width, const float& height,
	sf::Font* font, const std::string& text, const unsigned& charcter_size,
	const sf::Color& text_idle_color, const sf::Color& text_hover_color, const sf::Color& text_active_color,
	const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
	const sf::Color& outlineIdleColor, const sf::Color& outlineHoverColor, const sf::Color& outlineActiveColor,
	short unsigned id)

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

std::string GUI::Button::getText()
{
	return this->text.getString();
}

//Seters
void GUI::Button::setText(std::string text)
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

const bool GUI::DropDownList::getKeyTime()
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


////========================TextureSelector==========================////

//Initialisation
void GUI::TextureSelector::initBounds(const float& x, const float& y, const float& width_bounds, const float& height_bounds)
{
	this->bounds.setSize(sf::Vector2f(width_bounds, height_bounds));
	this->bounds.setPosition(x + 60.f, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));
}

void GUI::TextureSelector::initSpriteSheet(const float& x, const float& y, const sf::Texture& texture_sheet)
{
	this->sheet.setTexture(texture_sheet);
	this->sheet.setPosition(x + 60.f, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().height, this->sheet.getGlobalBounds().width));
	}
}

void GUI::TextureSelector::initSelector_TextureRect(const float& x, const float& y)
{
	//Selector
	this->selector.setPosition(x + 60.f, y);
	this->selector.setSize(sf::Vector2f(static_cast<float>(this->gridSize), static_cast<float>(this->gridSize)));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(2.f);
	this->selector.setOutlineColor(sf::Color::Red);

	//Texture rect
	this->textureRect.width = static_cast<int>(this->gridSize);
	this->textureRect.height = static_cast<int>(this->gridSize);
}

//Constructor
GUI::TextureSelector::TextureSelector(const float& x, const float& y, const float& width_bounds, const float& hight_bounds, 
	const unsigned& gridSize ,const sf::Texture& texture_sheet, sf::Font& font)
	:active(false), hiden(false), gridSize(gridSize), keyTime(0.f), keyTimeMax(5.f)
{
	this->initBounds(x, y, width_bounds, hight_bounds);
	this->initSpriteSheet(x, y, texture_sheet);
	this->initSelector_TextureRect(x, y);

	this->hideButton = new GUI::Button(x, y, 50.f, 50.f,
		&font, "TS", 30,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

GUI::TextureSelector::~TextureSelector()
{
	delete this->hideButton;
}

const sf::IntRect& GUI::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

//Accessors
const bool& GUI::TextureSelector::getActive() const
{
	return this->active;
}

const bool GUI::TextureSelector::getKeyTime()
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
void GUI::TextureSelector::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.f * dt;
	}
}

void GUI::TextureSelector::update(const sf::Vector2i& mousePosWIndow,const float& dt)
{
	this->updateKeyTime(dt);

	this->hideButton->update(static_cast<sf::Vector2f>(mousePosWIndow));

	if (this->hideButton->isPressed() && this->getKeyTime())
	{
		this->hiden = !this->hiden;
	}

	if (!this->hiden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWIndow)))
		{
			this->active = true;
		}
		else
		{
			this->active = false;
		}

		if (this->active)
		{
			this->mousePosGrid.x = (mousePosWIndow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWIndow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

			//Update texture rect
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void GUI::TextureSelector::render(sf::RenderTarget& target)
{
	if (!this->hiden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
		{
			target.draw(this->selector);
		}
	}
	this->hideButton->render(target);

}
