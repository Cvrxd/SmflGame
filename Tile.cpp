#include "stdafx.h"
#include "Tile.h"

Tile::Tile(const int& x, const int& y, const float& gridSizef, const sf::Texture& texture, const sf::IntRect& texture_rect, 
	const bool& collision, const short& type)
	: collision(collision), type(type), x(x), y(y)
{
	this->shape.setSize(sf::Vector2f(gridSizef, gridSizef));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition(static_cast<float>(x) * gridSizef, static_cast<float>(y) * gridSizef);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);
	//this->shape.setScale(2.f, 2.f);

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

const sf::Vector2f& Tile::getPositionF() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const short& Tile::getType() const
{
	return this->type;
}

const bool Tile::inersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

const int& Tile::getX()
{
	return this->x;
}

const int& Tile::getY()
{
	return this->y;
}

//Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target, const sf::Vector2f& player_position, sf::Shader* shader)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}
