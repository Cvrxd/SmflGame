#include "stdafx.h"
#include "BossEnemy.h"

//Init functions

inline void BossEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case NIGHTBORN:
		this->sprite.setScale(4.f, 4.f);

		this->createHitboxComponent(this->sprite, 100.f, 100.f, 100.f, 100.f);
		this->createMovementComponent(150.f, 900.f, 250.f);
		this->createAnimationComponent(texture_sheet);

		this->setOriginLeft = [&sprite]() 
		{
			sprite.setOrigin(80.f, 0.f);
			sprite.setScale(-4.f, 4.f);
		};

		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(4.f, 4.f);
		};

	default:
		break;
	}
}

inline void BossEnemy::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->addAnimations();
}

inline void BossEnemy::addAnimations()
{
	switch (this->type)
	{
	case NIGHTBORN:
		this->animationComponent.addAnimation("IDLE", 0, 0, 8, 0, 80, 80, 10.f);
		this->animationComponent.addAnimation("MOVE", 0, 1, 5, 1, 80, 80, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 2, 11, 2, 80, 80, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 4, 3, 80, 80, 8.f);
		this->animationComponent.addAnimation("DEATH", 0, 4, 22, 4, 80, 80, 8.f);
	default:
		break;
	}
}

//Constructors
BossEnemy::BossEnemy(const BossType& type, const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player)
	:Enemy(level, x, y, texture_sheet, player), 
	type(type)
{
	this->initStats();
	this->initComponents(texture_sheet, this->sprite);
	this->setPosition(x, y);
}

BossEnemy::~BossEnemy()
{
}

//Functions
inline void BossEnemy::updateAttack(const float& dt)
{
	if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()) && !this->isDead)
	{
		this->isAttaking = true;
	}

	if (this->isAttaking)
	{
		if (this->animationComponent.play("ATTACK", dt, true))
		{
			if (this->player->getHitRange().getGlobalBounds().intersects(this->getGlobalBounds()))
			{
				this->player->loseHP(this->statsComponent.damagePhysical);
			}
			this->isAttaking = false;
		}
	}
}

inline void BossEnemy::updateMovement(const float& dt)
{
	if (this->player->getPosition().x > this->getPosition().x)
	{
		this->move(1.f, 0.f, dt);
	}
	else if (this->player->getPosition().x < this->getPosition().x)
	{
		this->move(-1.f, 0.f, dt);
	}
	if (this->player->getPosition().y < this->getPosition().y)
	{
		this->move(0.f, -1.f, dt);
	}
	else if (this->player->getPosition().y > this->getPosition().y)
	{
		this->move(0, 1.f, dt);
	}
}

inline void BossEnemy::updateAnimations(const float& dt)
{
	if (this->takingHit)
	{
		this->stopVelocity();

		if (this->animationComponent.play("TAKE_HIT", dt, true))
		{
			this->takingHit = false;
		}
	}

	if (this->isDead)
	{
		this->stopVelocity();
		this->animationComponent.play("DEATH", dt, true);
	}

	if (this->movementComponent.getState(MOVING_RIGHT))
	{
		this->setOriginRight();
		this->animationComponent.play("MOVE", dt, this->movementComponent.getVelocity().x, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVING_LEFT))
	{
		this->setOriginLeft();
		this->animationComponent.play("MOVE", dt, this->movementComponent.getVelocity().x, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVE_UP))
	{
		this->animationComponent.play("MOVE", dt, this->movementComponent.getVelocity().y, this->movementComponent.getMaxVelocity());
	}
	else if (this->movementComponent.getState(MOVE_DOWN))
	{
		this->animationComponent.play("MOVE", dt, this->movementComponent.getVelocity().y, this->movementComponent.getMaxVelocity());
	}
}

void BossEnemy::updatePlayerImpact()
{
	if (this->player->getDamageRange().getGlobalBounds().intersects(this->getGlobalBounds()))
	{
		if (this->player->isDealingDmg())
		{
			this->takingHit = true;

			this->statsComponent.loseHP(this->player->getStatsComponent()->damagePhysical);

			if (this->statsComponent.hp == 0)
			{
				this->isDead = true;
			}
		}
	}
}

void BossEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent.update(dt);

	this->updatePlayerImpact();
	this->updateAttack(dt);
	this->updateMovement(dt);
	this->updateAnimations(dt);

	this->hitboxComponent.update();
}

void BossEnemy::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(this->sprite, shader);
	this->hitboxComponent.render(target);
}