#include "Player.h"

//Initialasation functions
void Player::initVariables()
{
}

void Player::initComponents()
{
}

//1468 / 9 = 162 x

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	
	this->animationComponent->addAnimation("IDLE_RIGHT", 0, 0, 9, 0, 162, 162, 10.f);
	this->animationComponent->addAnimation("WALK_RIGHT", 0, 1, 7, 1, 162, 162, 10.f);
}

Player::~Player()
{
}

//Functions

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	
	if(this->movementComponent->idle())
		this->animationComponent->play("IDLE_RIGHT", dt);
	else
		this->animationComponent->play("WALK_RIGHT", dt);
}
