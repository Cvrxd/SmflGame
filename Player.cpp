#include "stdafx.h"
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
	this->createHitboxComponent(this->sprite, 45.f, 48.f, 55.f, 55.f);
	this->createMovementComponent(270.f, 1200.f, 400.f);
	this->createAnimationComponent(texture_sheet);
	this->createLevelingComponent(1);
}

void Player::addAnimations()
{
	//Regular sprite
	this->animationComponent->addAnimation("IDLE", 0, 0, 3, 0, 50, 40, 13.f);
	this->animationComponent->addAnimation("MOVE", 0, 1, 5, 1, 50, 37, 9.f);
	this->animationComponent->addAnimation("ATTACK_FIRST", 0, 4, 8, 4, 50, 37, 6.f);
	this->animationComponent->addAnimation("ATTACK_SECOND", 0, 5, 8, 5, 50, 37, 6.f);
	this->animationComponent->addAnimation("CAST_SPELL", 0, 3, 8, 3, 50, 37, 10.f);
}

//Constructor
Player::Player(const float& x, const float& y, sf::Texture& texture_sheet)
{
	this->setPosition(x, y);
	this->initComponents(texture_sheet);
	this->addAnimations();
	this->sprite.setScale(2.8f, 2.8f);
}

Player::~Player()
{
}

//Accessors
LevelingComponent* Player::getLVLcomponent()
{
	return this->levelingComponent;
}

//Stat functions
void Player::gainEXP(const unsigned& exp)
{
	this->levelingComponent->gainEXP(exp);
}

void Player::loseHP(const int& hp)
{
	this->levelingComponent->loseHP(hp);
}

void Player::gainHP(const int& hp)
{
	this->levelingComponent->gainHP(hp);
}

//Functions
void Player::updateAttack(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->isAttacking = true;
	}
	if (this->isAttacking)
	{
		if (this->animationComponent->play("ATTACK_FIRST", dt, true))
		{
			if(this->animationComponent->play("ATTACK_SECOND", dt, true))
				this->isAttacking = false;
		}
	}
}

void Player::updateRegularKeyboard(const float& dt, sf::Vector2f mouse_pos_view)
{
	//Regular keyboardupdate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		this->animationComponent->play("CAST_SPELL", dt);
	}
	else if (this->movementComponent->getState(IDLE))
	{
		if (mouse_pos_view.x < this->hitboxComponent->getPositionHitbox().x)
		{
			this->sprite.setOrigin(50.f, 0.f);
			this->sprite.setScale(-2.8f, 2.8f);
		}
		else
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(2.8f, 2.8f);
		}

		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(2.8f, 2.8f);
		this->animationComponent->play("MOVE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(50.f, 0.f);
		this->sprite.setScale(-2.8f, 2.8f);
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

void Player::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent->update(dt);
	this->updateAttack(dt);
	this->updateRegularKeyboard(dt, mouse_pos_view);
	this->hitboxComponent->update();

	//Debug!
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());

		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}
	
	this->hitboxComponent->render(target);
}
