#include "stdafx.h"
#include "MeleEnemy.h"

//Init functions
inline void MeleEnemy::initComponents(sf::Texture& texture_sheet, sf::Sprite& sprite)
{
	switch (this->type)
	{
	case MeleEnemyType::MIMIC:
		this->sprite.setScale(3.f, 3.f);

		//Init components
		this->createHitboxComponent(this->sprite, 70.f, 120.f, 100.f, 100.f);
		this->createMovementComponent(80.f, 600.f, 100.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(100.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
		break;
	case MeleEnemyType::BRINGER_OF_DEATH:
		this->sprite.setScale(3.f, 3.f);

		//Init components
		this->createHitboxComponent(this->sprite, 250.f, 120.f, 100.f, 200.f);
		this->createMovementComponent(150.f, 850.f, 200.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(3.f, 3.f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(200.f, 0.f);
			sprite.setScale(-3.f, 3.f);
		};
		break;
	case MeleEnemyType::KNIGHT1:
		this->sprite.setScale(2.5f, 2.5f);

		//Init components
		this->createHitboxComponent(this->sprite, 200.f, 150.f, 120.f, 150.f);
		this->createMovementComponent(200.f, 1000.f, 350.f);
		this->createAnimationComponent(texture_sheet);

		//Sets origins
		this->setOriginLeft = [&sprite]()
		{
			sprite.setOrigin(200.f, 0.f);
			sprite.setScale(-2.5f, 2.5f);
		};
		this->setOriginRight = [&sprite]()
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(2.5f, 2.5f);
		};
		break;
	default:
		break;
	}
}

inline void MeleEnemy::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->addAnimations();
}

inline void MeleEnemy::addAnimations()
{
	switch (this->type)
	{
	case MeleEnemyType::MIMIC:
		this->animationComponent.addAnimation("MOVE", 0, 1, 3, 1, 108, 108, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 3, 0, 108, 108, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 1, 2, 108, 108, 20.f);
		this->animationComponent.addAnimation("DEATH", 0, 2, 3, 2, 108, 108, 20.f);
		break;
	case MeleEnemyType::BRINGER_OF_DEATH:
		this->animationComponent.addAnimation("MOVE", 0, 0, 7, 0, 140, 93, 20.f);
		this->animationComponent.addAnimation("ATTACK", 0, 1, 9, 1, 140, 93, 10.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 2, 2, 2, 140, 93, 20.f);
		this->animationComponent.addAnimation("DEATH", 2, 2, 11, 2, 140, 93, 15.f);
		break;
	case MeleEnemyType::KNIGHT1:
		this->animationComponent.addAnimation("MOVE", 0, 2, 7, 2, 180, 180, 13.f);
		this->animationComponent.addAnimation("ATTACK", 0, 0, 6, 0, 180, 180, 11.f);
		this->animationComponent.addAnimation("TAKE_HIT", 0, 3, 3, 3, 180, 180, 14.f);
		this->animationComponent.addAnimation("DEATH", 0, 1, 10, 1, 180, 180, 11.f);
		break;
	default:
		break;
	}
}

//Constructors
MeleEnemy::MeleEnemy(const MeleEnemyType& type, const int& level, const float& x, const float& y, sf::Texture& texture_sheet, Player* player)
	:Enemy(level, x, y, texture_sheet, player),
	type(type)
{
	this->initStats();
	this->initComponents(texture_sheet, this->sprite);
	this->setPosition(x, y);
}

MeleEnemy::MeleEnemy(MeleEnemy&& other)
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
	//
	this->takeHitAnimation = other.takeHitAnimation;
	this->takeHitSprite = other.takeHitSprite;

	other.player = nullptr;
}

MeleEnemy::~MeleEnemy()
{
}

//Functions
inline void MeleEnemy::updateAttack(const float& dt)
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

inline void MeleEnemy::updateMovement(const float& dt)
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

inline void MeleEnemy::updateAnimations(const float& dt)
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
		this->skillsImpactSprites[this->player->getUsingSkilltype()].first.setPosition(this->getPosition().x - 40, this->getPosition().y - 40);

		if (this->skillsImpactAnimations[this->player->getUsingSkilltype()].play("SKILL_IMPACT", dt, true))
		{
			this->skillImpact = false;
		}
	}

	if (this->statsComponent.hp == 0)
	{
		this->stopVelocity();
		if (this->animationComponent.play("DEATH", dt, true))
		{
			this->player->gainEXP(this->statsComponent.level * 2);

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

inline void MeleEnemy::updatePlayerImpact(const float& dt)
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

void MeleEnemy::enemyDead(const float& dt)
{

}

void MeleEnemy::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	this->movementComponent.update(dt);

	this->updatePlayerImpact(dt);
	this->updateAttack(dt);
	this->updateMovement(dt);
	this->updateAnimations(dt);

	this->hitboxComponent.update();
}

void MeleEnemy::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(this->sprite, shader);

	if (this->hitImpact)
	{
		target.draw(this->takeHitSprite.second);
	}
	if (this->skillImpact)
	{
		target.draw(this->skillsImpactSprites[this->player->getUsingSkilltype()].first);
	}

	//this->hitboxComponent.render(target);
}