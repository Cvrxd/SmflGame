#include "stdafx.h"
#include "EnemyHealthBar.h"

//Initialisation
void EnemyHealthBar::initTextures()
{
	this->backgroundTexture.loadFromFile("Textures/hud/game_hud/background2.png");
	this->backgroundRect.setTexture(&this->backgroundTexture);
	this->backgroundRect.setSize(sf::Vector2f(256, 32));

	this->healthTexture.loadFromFile("Textures/hud/game_hud/health_bar.png");
	this->healthRect.setTexture(&this->healthTexture);
	this->healthRect.setSize(sf::Vector2f(256, 32));
}

//constructor
EnemyHealthBar::EnemyHealthBar(const int* hp)
	: hp(hp), hpMAX(*hp)
{
	this->initTextures();
}

EnemyHealthBar::~EnemyHealthBar()
{
}

void EnemyHealthBar::updateOffsetX()
{
	this->offsetX += 5;
}

//Functions
void EnemyHealthBar::update(const float& dt, const sf::Vector2f& position)
{
	this->backgroundRect.setPosition(position.x - 50, position.y - 20);
	this->healthRect.setPosition(position.x + this->offsetX - 50, position.y - 20);

	
	this->healthRect.setSize(sf::Vector2f(this->backgroundRect.getSize().x / this->hpMAX * *(this->hp), 
		this->healthRect.getSize().y));
}

void EnemyHealthBar::render(sf::RenderTarget& target)
{
	target.draw(this->backgroundRect);
	target.draw(this->healthRect);
}
