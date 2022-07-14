#include "stdafx.h"
#include "Gui.h"

//============================//
//TextureSelector=============//
//============================//

//Initialisation
void GUI::TextureSelector::initBounds(const float& x, const float& y, const float& width_bounds, const float& height_bounds)
{
	this->bounds.setSize(sf::Vector2f(width_bounds, height_bounds));
	this->bounds.setPosition(x + gridSize, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));
}

void GUI::TextureSelector::initSpriteSheet(const float& x, const float& y, const sf::Texture& texture_sheet)
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

void GUI::TextureSelector::initSelector_TextureRect(const float& x, const float& y)
{
	//Selector
	this->selector.setPosition(x + gridSize, y);
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
	const unsigned& gridSize, const sf::Texture& texture_sheet, sf::Font& font) noexcept
	:active(false),
	hiden(false),
	gridSize(gridSize),
	keyTime(0.f), keyTimeMax(5.f)
{
	this->initBounds(x, y, width_bounds, hight_bounds);
	this->initSpriteSheet(x, y, texture_sheet);
	this->initSelector_TextureRect(x, y);

	this->hideButton = std::make_unique<GUI::Button>(x - 40, y - 10, 50.f, 50.f,
		&font, "H", 40,
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

void GUI::TextureSelector::update(const sf::Vector2i& mousePosWIndow, const float& dt)
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
