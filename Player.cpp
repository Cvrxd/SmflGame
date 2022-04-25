#include "Player.h"

//Initialasation functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	this->createMovementComponent(250.f, 10.f, 4.f);
}

Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{
}

//Functions