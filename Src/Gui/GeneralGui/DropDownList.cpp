#include "stdafx.h"
#include "Gui.h"

//============================//
//DropDownList================//
//============================//

//Constructor
GUI::DropDownList::DropDownList(const float& x, const float& y, const float& width, const float& hight,
	sf::Font& font, std::string text_list[], const unsigned& number_of_elements, const unsigned& default_index) noexcept
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
		this->dropBox.push_back(std::make_shared<GUI::Button>(x, y + ((i + 1) * hight) + 20, width + 8, hight,
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

const bool& GUI::DropDownList::isActive() const
{
	return this->showDropBox;
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
