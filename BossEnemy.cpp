#include "stdafx.h"
#include "BossEnemy.h"

//Init functions
inline void BossEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case BossType::NIGHTBORN:

		this->sprite.setScale(4.f, 4.f);

		//Init components
		this->createHitboxComponent(this->sprite, 100.f, 100.f, 100.f, 100.f);
		this->createMovementComponent(150.f, 900.f, 250.f);
		this->createAnimationComponent(texture_sheet);
		this->initImpactAnimations();

		//Sets origins
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

		break;
	case BossType::FIRE_DEMON:
		this->sprite.setScale(4.f, 4.f);

		//Init components
		this->createHitboxComponent(this->sprite, 300.f, 300.f, 300.f, 350.f);
		this->createMovementComponent(100.f, 800.f, 230.f);
		this->createAnimationComponent(texture_sheet);
		this->initImpactAnimations();

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(4.f, 4.f);
		};

		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(250.f, 0.f);
			sprite.setScale(-4.f, 4.f);
		};


		break;
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
	case BossType::NIGHTBORN:
		//Regular animations
		this->animationComponent.addAnimation("MOVE", 0, 1, 5, 1, 80, 80, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 2, 11, 2, 80, 80, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 4, 3, 80, 80, 10.f);
		this->animationComponent.addAnimation("DEATH", 0, 4, 22, 4, 80, 80, 8.f);
		break;

	case BossType::FIRE_DEMON:
		this->animationComponent.addAnimation("MOVE", 0, 1, 11, 1, 288, 160, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 2, 14, 2, 288, 160, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 4, 3, 288, 160, 10.f);
		this->animationComponent.addAnimation("DEATH", 0, 4, 21, 4, 288, 160, 10.f);

		break;
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

BossEnemy::BossEnemy(BossEnemy&& other)
	:Enemy(this->statsComponent.level, this->getPosition().x, this->getPosition().y, *this->textureSheet, this->player)
{
	this->animationComponent = other.animationComponent;
	this->dropComponent = other.dropComponent;
	this->hitboxComponent = other.hitboxComponent;
	this->isAttaking = other.isAttaking;
	this->isDead = other.isDead;
	this->movementComponent = other.movementComponent;
	this->setOriginLeft = other.setOriginLeft;
	this->setOriginRight = other.setOriginRight;
	this->sprite = other.sprite;
	this->statsComponent = other.statsComponent;
	this->hitImpact = other.hitImpact;
	this->skillImpact = other.skillImpact;
	this->type = other.type;
	this->skillImpactAnimation = other.skillImpactAnimation;
	this->skillImpactSprite = other.skillImpactSprite;
	this->takeHitAnimation = other.takeHitAnimation;
	this->takeHitSprite = other.takeHitSprite;

	other.player = nullptr;
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
	if (this->isTakingDamage)
	{
		this->stopVelocity();

		if (this->animationComponent.play("TAKE_HIT", dt, true))
		{
			this->isTakingDamage = false;
		}
	}

	//Player hit
	if (this->hitImpact)
	{
		this->takeHitSprite.second.setPosition(this->getPosition());

		if (this->takeHitAnimation.play("TAKE_HIT1", dt, true))
		{
			if (this->takeHitAnimation.play("TAKE_HIT2", dt, true))
			{
				this->hitImpact = false;
			}
		}
	}

	//Plyaer skill
	if (this->skillImpact)
	{
		this->skillImpactSprite.second.setPosition(this->getPosition());

		if (this->skillImpactAnimation.play("SKILL_IMPACT", dt, true))
		{
			this->skillImpact = false;
		}
	}

	if (this->statsComponent.hp == 0)
	{
		this->stopVelocity();
		if (this->animationComponent.play("DEATH", dt, true))
		{
			this->player->addPotions(HEALTH);
			this->player->addPotions(MANA);
			this->player->gainEXP(this->statsComponent.level * 5);

			this->isDead = true;
		}
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

inline void BossEnemy::updatePlayerImpact(const float& dt)
{
	//Player damage impact
	if (this->player->getDamageRange().getGlobalBounds().intersects(this->getGlobalBounds()))
	{
		if (this->player->isDealingDmg())
		{
			this->isTakingDamage = true;
			this->hitImpact = true;

			this->statsComponent.loseHP(this->player->getStatsComponent()->damagePhysical);
		}
	}
	//Skill damage impact
	if (this->player->usingSkill())
	{
		if (this->player->getSkillComponent()->getDamageArea().getGlobalBounds().intersects(this->getGlobalBounds()))
		{
			this->isTakingDamage = true;
			this->skillImpact = true;

			this->statsComponent.loseHP(this->player->getStatsComponent()->damageMagical);
		}
	}
}

void BossEnemy::enemyDead(const float& dt)
{

}

void BossEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent.update(dt);

	this->updatePlayerImpact(dt);
	this->updateAttack(dt);
	this->updateMovement(dt);
	this->updateAnimations(dt);

	this->hitboxComponent.update();
}

void BossEnemy::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(this->sprite, shader);

	if (this->hitImpact)
	{
		target.draw(this->takeHitSprite.second);
	}
	if (this->skillImpact)
	{
		target.draw(this->skillImpactSprite.second);
	}

	//this->hitboxComponent.render(target);
}