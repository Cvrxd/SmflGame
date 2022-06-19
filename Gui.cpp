#include "stdafx.h"
#include "Gui.h"

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

//============================//
//DropDownList================//
//============================//

//Constructor
GUI::DropDownList::DropDownList(const float& x, const float& y, const float& width, const float& hight, 
	sf::Font& font, std::string text_list[], const unsigned& number_of_elements,const unsigned& default_index) noexcept
	:font(font), showDropBox(false), keyTimeMax(2.f), keyTime(0.f)
{
	this->activeBox = std::make_shared<GUI::Button>(x, y + 20, width + 8, hight,
		&this->font, text_list[default_index], 28,
		sf::Color(255, 255, 255, 160), sf::Color(252, 252, 252, 200), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 50)
	);

	this->dropBox.reserve(number_of_elements);

	for (unsigned short i = 0; i < number_of_elements; ++i)
	{
		this->dropBox.push_back(std::make_shared<GUI::Button>(x, y + ((i+1) * hight) + 20, width + 8, hight,
			&this->font, text_list[i], 28,
			sf::Color(255, 255, 255, 150), sf::Color(252, 252, 252, 252), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
			sf::Color(255, 255, 255, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0), i
		));
	}
	
}

GUI::DropDownList::~DropDownList()
{
}

//Accessors
const unsigned short& GUI::DropDownList::getActiveBoxId() const
{
	return this->activeBox->getId();
}

const sf::Vector2f GUI::DropDownList::getPosition() const
{
	return this->activeBox.operator*().getPosition();
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
inline void GUI::DropDownList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.f * dt;
	}
}

void GUI::DropDownList::update(const sf::Vector2i& mousePosition, const float& dt)
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

//============================//
//TextureSelector=============//
//============================//

//Initialisation
inline void GUI::TextureSelector::initBounds(const float& x, const float& y, const float& width_bounds, const float& height_bounds)
{
	this->bounds.setSize             (sf::Vector2f(width_bounds, height_bounds));
	this->bounds.setPosition         (x + gridSize, y);
	this->bounds.setFillColor        (sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness (1.f);
	this->bounds.setOutlineColor     (sf::Color(255, 255, 255, 200));
}

inline void GUI::TextureSelector::initSpriteSheet(const float& x, const float& y, const sf::Texture& texture_sheet)
{
	this->sheet.setTexture(texture_sheet);
	this->sheet.setPosition(x + this->gridSize, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, int(this->bounds.getGlobalBounds().width), int(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, int(this->bounds.getGlobalBounds().height), int(this->sheet.getGlobalBounds().width)));
	}
}

inline void GUI::TextureSelector::initSelector_TextureRect(const float& x, const float& y)
{
	//Selector
	this->selector.setPosition         (x + gridSize, y);
	this->selector.setSize             (sf::Vector2f(static_cast<float>(this->gridSize), static_cast<float>(this->gridSize)));
	this->selector.setFillColor        (sf::Color::Transparent);
	this->selector.setOutlineThickness (2.f);
	this->selector.setOutlineColor     (sf::Color::Red);

	//Texture rect
	this->textureRect.width  = static_cast<int>(this->gridSize);
	this->textureRect.height = static_cast<int>(this->gridSize);
}

//Constructor
GUI::TextureSelector::TextureSelector(const float& x, const float& y, const float& width_bounds, const float& hight_bounds, 
	const unsigned& gridSize ,const sf::Texture& texture_sheet, sf::Font& font) noexcept
	:active(false), hiden(false), gridSize(gridSize), keyTime(0.f), keyTimeMax(5.f)
{
	this->initBounds               (x, y, width_bounds, hight_bounds);
	this->initSpriteSheet          (x, y, texture_sheet);
	this->initSelector_TextureRect (x, y);

	this->hideButton = std::make_unique<GUI::Button>(x - 40, y - 10, 50.f, 50.f,
		&font, "H", 30,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

GUI::TextureSelector::~TextureSelector()
{
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

void GUI::TextureSelector::pressButton()
{
	if (this->hiden)
	{
		this->hideButton->setText("H");
	}
	else
	{
		this->hideButton->setText("S");
	}
	this->hiden = !this->hiden;
}

//Functions
inline void GUI::TextureSelector::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.f * dt;
	}
}

void GUI::TextureSelector::update(const sf::Vector2i& mousePosWIndow,const float& dt)
{
	this->updateKeyTime(dt);

	this->hideButton->update(mousePosWIndow);

	if (this->hideButton->isPressed() && this->getKeyTime())
	{
		if (this->hiden)
		{
			this->hideButton->setText("H");
		}
		else
		{
			this->hideButton->setText("S");
		}
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
