#include "stdafx.h"
#include "EnemyGUI.h"

//===========================
//EnemyHealthBar=============
//===========================

//Initialisation
inline void EnemyGUI::EnemyHealthBar::initTextures()
{
	this->backgroundTexture.loadFromFile("Textures/hud/game_hud/background2.png");
	this->backgroundRect.setTexture(&this->backgroundTexture);
	this->backgroundRect.setSize(sf::Vector2f(256, 32));

	this->healthTexture.loadFromFile("Textures/hud/game_hud/health_bar.png");
	this->healthRect.setTexture(&this->healthTexture);
	this->healthRect.setSize(sf::Vector2f(256, 32));
}

//Constructor
EnemyGUI::EnemyHealthBar::EnemyHealthBar(const int* hp) noexcept
	: hp(hp), hpMAX(*hp)
{
	this->initTextures();
}

EnemyGUI::EnemyHealthBar::~EnemyHealthBar()
{
}

//Functions
void EnemyGUI::EnemyHealthBar::updateOffsetX()
{
	this->offsetX += 10.f / float(this->hpMAX / 3.f) + 0.1f;
}

void EnemyGUI::EnemyHealthBar::update(const float& dt, const sf::Vector2f& position)
{
	this->backgroundRect.setPosition(position.x - 30, position.y - 20);
	this->healthRect.setPosition(position.x + this->offsetX - 30, position.y - 20);

	
	this->healthRect.setSize(sf::Vector2f(this->backgroundRect.getSize().x / this->hpMAX * *(this->hp), 
		this->healthRect.getSize().y));

}

void EnemyGUI::EnemyHealthBar::render(sf::RenderTarget& target)
{
	target.draw(this->healthRect);
	target.draw(this->backgroundRect);
}

//======================
//Enemy LVL icon========
//======================

//Initialisation
inline void EnemyGUI::EnemyLevelIcon::initVariables(const sf::Font& font)
{
	this->backgroundTexture.loadFromFile("Textures/hud/game_hud/icons.png");
	this->backgroundRect.setTexture(&this->backgroundTexture);
	this->backgroundRect.setTextureRect(sf::IntRect(158, 54, 32, 29));
	this->backgroundRect.setSize(sf::Vector2f(40.f, 40.f));

	this->lvlText.setFont(font);
	this->lvlText.setCharacterSize(30);
	this->lvlText.setString(std::to_string(*this->lvl));
	if (*this->lvl < 9)
	{
		this->offsetX -= 9.f;
	}

	this->updateText();

}

//Constructor
EnemyGUI::EnemyLevelIcon::EnemyLevelIcon(const int* lvl, const int* playerLvl, const sf::Font& font) noexcept
	: lvl(lvl), playerLvl(playerLvl)
{
	this->initVariables(font);
}

EnemyGUI::EnemyLevelIcon::~EnemyLevelIcon()
{
}

//Functions
void EnemyGUI::EnemyLevelIcon::updateText()
{
	if (*this->playerLvl - *this->lvl < 6 && *this->playerLvl - *this->lvl > -5)
	{
		this->lvlText.setFillColor(sf::Color::White);
	}
	else if (*this->playerLvl - *this->lvl > 5)
	{
		this->lvlText.setFillColor(sf::Color::Green);
	}
	else if (*this->playerLvl - *this->lvl < 6 && *this->playerLvl - *this->lvl > -10)
	{
		this->lvlText.setFillColor(sf::Color::Yellow);
	}
	else
	{
		this->lvlText.setFillColor(sf::Color::Red);
	}
}

void EnemyGUI::EnemyLevelIcon::updateOffsetX()
{
}

void EnemyGUI::EnemyLevelIcon::update(const float& dt, const sf::Vector2f& position)
{
	this->lvlText.setPosition(position.x + 5 - this->offsetX, position.y - 25);
	this->backgroundRect.setPosition(position.x -45, position.y - 25);
}

void EnemyGUI::EnemyLevelIcon::render(sf::RenderTarget& target)
{
	target.draw(this->backgroundRect);
	target.draw(this->lvlText);
}
