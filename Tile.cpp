#include "stdafx.h"
#include "Tile.h"

Tile::Tile(const float& x, const float& y, const float& gridSizef, const sf::Texture& texture, const sf::IntRect& texture_rect, 
	const bool& collision, const short& type)
	: collision(collision), type(type), x(x), y(y)
{
	this->shape.setSize(sf::Vector2f(gridSizef, gridSizef));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition(x, y);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);

	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
}

Tile::~Tile()
{
}

//Accessors
const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

	return ss.str();
}

void Tile::setX(const unsigned& x)
{
	this->x = x;
}

void Tile::setY(const unsigned& y)
{
	this->y = y;
}

const unsigned& Tile::getX()
{
	return this->x;
}

const unsigned& Tile::getY()
{
	return this->y;
}



//Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
