#include "stdafx.h"
#include "Tile.h"

Tile::Tile(const float& x, const float& y, const float& gridSizef)
	: added(true)
{
	this->shape.setSize(sf::Vector2f(gridSizef, gridSizef));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(x, y);
}

Tile::~Tile()
{
}

//Accessors
const sf::Vector2u& Tile::getCoordinates()
{
	return sf::Vector2u(this->x, this->y);
}

//Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
