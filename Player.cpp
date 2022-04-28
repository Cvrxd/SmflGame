#include "Player.h"

//Initialasation functions
void Player::initVariables()
{
	
}

void Player::createAnimationComponent(sf::Texture& texture_sheet)
{
	//Regular texture
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Player::initComponents(sf::Texture& texture_sheet)
{
	this->createHitboxComponent(this->sprite, 50.f, 50.f, 60.f, 60.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	
	this->createAnimationComponent(texture_sheet);

	/*
	this->createHitboxComponent(this->sprite, 160.f, 180.f, 80.f, 80.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 0, 0, 7, 0, 160, 128, 11.f);
	this->animationComponent->addAnimation("MOVE", 0, 1, 7, 1, 160, 128, 7.f);
	this->animationComponent->addAnimation("ATTACK", 0, 2, 12, 3, 160, 128, 6.f);
	*/
}

void Player::addAnimations()
{
	//Regular sprite
	this->animationComponent->addAnimation("IDLE", 0, 0, 3, 0, 50, 40, 13.f);
	this->animationComponent->addAnimation("MOVE", 1, 8, 4, 8, 50, 37, 8.f);
	this->animationComponent->addAnimation("ATTACK", 0, 4, 8, 4, 50, 37, 7.f);
	this->animationComponent->addAnimation("CAST_SPELL", 0, 3, 8, 3, 50, 37, 10.f);
}

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->sprite.setScale(3.f, 3.f);
	this->setPosition(x, y);
	this->initComponents(texture_sheet);
	this->addAnimations();
}

Player::~Player()
{
}

//Functions

void Player::updateRegularKeyboard(const float& dt)
{
	//Regular keyboardupdate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		this->animationComponent->play("CAST_SPELL", dt, true);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->animationComponent->play("ATTACK", dt, true);
	}
	else if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(3.f, 3.f);
		this->animationComponent->play("MOVE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(50.f, 0.f);
		this->sprite.setScale(-3.f, 3.f);
		this->animationComponent->play("MOVE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVE_UP))
	{
		this->animationComponent->play("MOVE", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVE_DOWN))
	{
		this->animationComponent->play("MOVE", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateRegularKeyboard(dt);

	this->hitboxComponent->update();	
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitboxComponent->render(target);
}
