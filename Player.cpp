#include "stdafx.h"
#include "Player.h"

#define SPTIRES_SETSCALE_LEFT this->sprite.setOrigin(50.f, 0.f);\
							this->sprite.setScale(-2.8f, 2.8f);\
							this->sprites[0].second.setOrigin(50.f, 0.f);\
							this->sprites[0].second.setScale(-4.f, 4.f);\
							this->sprites[1].second.setScale(-4.f, 4.f);\
							this->sprites[2].second.setScale(-4.f, 4.f)

#define SPTIRES_SETSCALE_RIGHT this->sprite.setOrigin(0.f, 0.f);\
							this->sprite.setScale(2.8f, 2.8f);\
							this->sprites[0].second.setOrigin(0.f, 0.f);\
							this->sprites[0].second.setScale(4.f, 4.f);\
							this->sprites[1].second.setScale(4.f, 4.f);\
							this->sprites[2].second.setScale(4.f, 4.f)

//Initialasation functions
inline void Player::initVariables()
{
	this->sprites.resize(3);
	this->hitAnimations.resize(3);

	this->sprites[0].first.loadFromFile("Textures/animations/hit/swing02.png");
	this->sprites[0].second.setScale(4.f, 4.f);

	this->sprites[1].first.loadFromFile("Textures/animations/hit/hit01.png");
	this->sprites[1].second.setScale(4.f, 4.f);

	this->sprites[2].first.loadFromFile("Textures/animations/hit/circle02.png");
	this->sprites[2].second.setScale(4.f, 4.f);
}

inline void Player::createAnimationComponent(sf::Texture& texture_sheet)
{
	//Regular texture
	for (int i = 0; i < this->hitAnimations.size(); ++i)
	{
		this->hitAnimations[i] = AnimationComponent(&this->sprites[i].second, &this->sprites[i].first);
	}

	this->animationComponent = AnimationComponent(&this->sprite, &texture_sheet);
	this->addAnimations();
}

inline void Player::initComponents(sf::Texture& texture_sheet)
{
	this->createHitboxComponent(this->sprite, 45.f, 48.f, 55.f, 55.f);
	this->createMovementComponent(270.f, 1200.f, 400.f);
	this->createAnimationComponent(texture_sheet);
}

inline void Player::addAnimations()
{
	//Regular sprite
	this->animationComponent.addAnimation("IDLE", 0, 0, 3, 0, 50, 40, 13.f);
	this->animationComponent.addAnimation("MOVE", 0, 1, 5, 1, 50, 37, 9.f);
	this->animationComponent.addAnimation("ATTACK_FIRST", 0, 4, 8, 4, 50, 37, 6.f);
	this->animationComponent.addAnimation("CAST_SPELL", 0, 3, 8, 3, 50, 37, 10.f);

	//Hit sprites
	this->hitAnimations[0].addAnimation("HIT", 0, 0, 10, 0, 64, 64, 5.f);

	this->hitAnimations[1].addAnimation("HIT1", 0, 0, 4, 0, 64, 64, 6.f);
	this->hitAnimations[1].addAnimation("HIT2", 0, 1, 4, 1, 64, 64, 6.f);

	this->hitAnimations[2].addAnimation("HIT1", 0, 0, 3, 0, 64, 64, 6.f);
	this->hitAnimations[2].addAnimation("HIT2", 0, 1, 3, 1, 64, 64, 6.f);
}

//Constructor
Player::Player(const float& x, const float& y, sf::Texture& texture_sheet) 
	: currentHitAnimation(0),
	statsComponent(1),
	animationComponent(&this->sprite, &texture_sheet),
	skillsComponent(this->statsComponent)
{
	this->initVariables();
	this->setPosition(x, y);
	this->initComponents(texture_sheet);
	this->sprite.setScale(2.8f, 2.8f);
}

Player::~Player()
{
}

//Accessors
StatsComponent* Player::getStatsComponent()
{
	return &this->statsComponent;
}

SkillsComponent* Player::getSkillComponent()
{
	return &this->skillsComponent;
}

//Stat functions
void Player::gainEXP(const unsigned& exp)
{
	this->statsComponent.gainEXP(exp);
}

void Player::gainHP(const int& hp)
{
	this->statsComponent.gainHP(hp);
}

void Player::loseHP(const int& hp)
{
	this->statsComponent.loseHP(hp);
}

void Player::gainMP(const int& mp)
{
	this->statsComponent.gainMP(mp);
}

void Player::loseMP(const int& mp)
{
	this->statsComponent.loseMP(mp);
}

void Player::gainArmor(const int& armor)
{
	this->statsComponent.gainArmor(armor);
}

void Player::addItem(const Items& item)
{
	this->statsComponent.addItem(item);
}

void Player::addPotions(const Potions& potion_type)
{
	this->skillsComponent.addPotion(potion_type);
}

void Player::usePotions(const Potions& potion_type)
{
	this->skillsComponent.usePotion(potion_type);
}

//Functions
inline void Player::updateAttack(const float& dt, sf::Vector2f mouse_pos_view)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->isAttacking = true;
		this->isHit = true;
	}
	if (this->isAttacking)
	{
		if (mouse_pos_view.x < this->hitboxComponent->getPositionHitbox().x)
		{
			SPTIRES_SETSCALE_LEFT;
		}
		else
		{
			SPTIRES_SETSCALE_RIGHT;
		}
		if (this->animationComponent.play("ATTACK_FIRST", dt, true))
		{
			this->isAttacking = false;
		}
	}
	if (this->isHit)
	{
		if (this->currentHitAnimation == 0)
		{
			this->sprites[currentHitAnimation].second.setPosition(this->getPosition().x - 80, this->getCenter().y - 150);
			if (this->hitAnimations[currentHitAnimation].play("HIT", dt, true))
			{
				this->isHit = false;
				if (++this->currentHitAnimation == this->hitAnimations.size())
				{
					this->currentHitAnimation = 0;
				}
			}
		}
		else
		{
			this->sprites[currentHitAnimation].second.setPosition(this->getPosition().x + 50, this->getCenter().y - 150);
			if (this->hitAnimations[currentHitAnimation].play("HIT1", dt, true))
			{
				if (this->hitAnimations[currentHitAnimation].play("HIT2", dt, true))
				{
					this->isHit = false;
					if (++this->currentHitAnimation == this->hitAnimations.size())
					{
						this->currentHitAnimation = 0;
					}
				}
			}
		}
	}
}

inline void Player::updateRegularKeyboard(const float& dt, sf::Vector2f mouse_pos_view)
{
	//Regular keyboardupdate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		this->animationComponent.play("CAST_SPELL", dt);
	}
	else if (this->movementComponent->getState(IDLE))
	{
		if (mouse_pos_view.x < this->hitboxComponent->getPositionHitbox().x)
		{
			SPTIRES_SETSCALE_LEFT;
		}
		else
		{
			SPTIRES_SETSCALE_RIGHT;
		}

		this->animationComponent.play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		SPTIRES_SETSCALE_RIGHT;

		this->animationComponent.play("MOVE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		SPTIRES_SETSCALE_LEFT;

		this->animationComponent.play("MOVE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVE_UP))
	{
		this->animationComponent.play("MOVE", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVE_DOWN))
	{
		this->animationComponent.play("MOVE", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent->update(dt);
	this->updateRegularKeyboard(dt, mouse_pos_view);
	this->updateAttack(dt, mouse_pos_view);
	this->skillsComponent.update(dt, mouse_pos_view, this->getCenter());
	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());

		target.draw(this->sprite, shader);
		if (this->isHit)
		{
			target.draw(this->sprites[currentHitAnimation].second);
		}

		this->skillsComponent.render(target);
	}
	else
	{
		target.draw(this->sprite);
	}
	
	this->hitboxComponent->render(target);
}
